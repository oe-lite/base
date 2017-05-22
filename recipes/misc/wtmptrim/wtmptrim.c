/*
 * Copyright (C) 2017 DEIF A/S
 *
 * Author: Rasmus Villemoes <ravi@prevas.dk>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */

#define _GNU_SOURCE
#include <assert.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utmp.h>

#ifndef DEFAULT_WTMPFILE
#define DEFAULT_WTMPFILE "/var/log/wtmp"
#endif
#ifndef DEFAULT_MAXSIZE
#define DEFAULT_MAXSIZE 250000
#endif

static int no_truncate = 0;
static size_t maxsize = DEFAULT_MAXSIZE;
static char *tmppath;

static int
copy_data(int dst, int src, size_t max)
{
	ssize_t i;
	size_t r, s, w, total = 0;
	char buf[100*sizeof(struct utmp)];

	while (total < max) {
		s = max - total;
		if (s > sizeof(buf))
			s = sizeof(buf);
		else
			s -= s % sizeof(struct utmp);
		assert(s <= sizeof(buf));
		assert(s % sizeof(struct utmp) == 0);
		for (r = 0; r < s; r += i) {
			i = read(src, buf + r, s - r);
			if (i < 0) {
				warn("read()");
				return 1;
			}
			if (i == 0)
				break;
		}
		if (!r)
			break;
		if (r % sizeof(struct utmp) != 0) {
			warnx("EOF in the middle of a utmp record");
			return 1;
		}
		for (w = 0; w < r; w += i) {
			i = write(dst, buf + w, r - w);
			if (i < 0) {
				warn("write()");
				return 1;
			}
			assert(i != 0);
		}
		total += r;
	}
	return 0;
}

static void
free_tmppath(void)
{
	free(tmppath);
	tmppath = NULL;
}

/* This is a no-op if we don't own tmppath - which we do if and only if tmppath is non-NULL. */
static void
remove_tmpfile(void)
{
	if (!tmppath)
		return;
	if (unlink(tmppath))
		warn("unlink(%s)", tmppath);
	free_tmppath();
}

static int
create_tmpfile(const char *wtmppath, const struct stat *st)
{
	int fd;

	if (asprintf(&tmppath, "%s.XXXXXX", wtmppath) < 0) {
		tmppath = NULL; /* asprintf doesn't guarantee not touching it */
		warn("asprintf()");
		return -1;
	}
	fd = mkstemp(tmppath);
	if (fd < 0) {
		warn("mkstemp()");
		free_tmppath();
		return -1;
	}

	if (fchmod(fd, st->st_mode)) {
		warn("fchmod()");
		goto err;
	}
	if (fchown(fd, st->st_uid, st->st_gid)) {
		warn("fchown()");
		goto err;
	}
	return fd;

err:
	if (close(fd) < 0)
		warn("close()");
	remove_tmpfile();
	return -1;
}

static int
open_wtmp(const char *wtmppath, struct stat *st)
{
	int fd;
	struct stat st2;

	fd = open(wtmppath, O_RDWR | O_NOFOLLOW | O_CLOEXEC);
	if (fd < 0) {
		warn("open(%s)", wtmppath);
		return -1;
	}
	if (flock(fd, LOCK_EX) < 0) {
		warn("flock()");
		goto err;
	}
	if (fstat(fd, st) < 0) {
		warn("fstat()");
		goto err;
	}
	/*
	 * Subtle: We must check that we have a flock on the file on
	 * disk. Some other process might have done the trimming
	 * concurrently - in that case, once we return from flock,
	 * fd refers to the now-unlinked old wtmp file.
	 */
	if (stat(wtmppath, &st2) < 0) {
		warn("stat()");
		goto err;
	}
	if (st->st_dev != st2.st_dev || st->st_ino != st2.st_ino) {
		warnx("lost race with other process");
		goto err;
	}
	return fd;
err:
	(void) close(fd);
	return -1;
}

static int
trim_wtmp(const char *wtmppath)
{
	struct stat st;
	off_t offset;
	int fd = -1, tmpfd = -1;
	int ret = 1;

	fd = open_wtmp(wtmppath, &st);
	if (fd < 0)
		goto out;

	if (st.st_size % sizeof(struct utmp) != 0) {
		warnx("the size of %s (%jd) is not a multiple of sizeof(struct utmp)==%zu",
		     wtmppath, (intmax_t)st.st_size, sizeof(struct utmp));
		goto out;
	}
	if (st.st_size <= (off_t)maxsize) {
		ret = 0;
		goto out;
	}
	/*
	 * Round maxsize down to a multiple of the record size, then
	 * seek to an offset maxsize from the end. We'll read until
	 * EOF, so we might still end up with a new file slightly
	 * larger than maxsize.
	 */
	maxsize -= maxsize % sizeof(struct utmp);
	offset = st.st_size - maxsize;
	assert(offset % sizeof(struct utmp) == 0);
	if (lseek(fd, offset, SEEK_SET) != offset) {
		warn("lseek()");
		goto out;
	}

	tmpfd = create_tmpfile(wtmppath, &st);
	if (tmpfd < 0)
		goto out;
	/*
	 * Copy from fd to tmpfd until we reach EOF in fd. We allow up
	 * to ~1.5% more than maxsize to catch a few logins done since
	 * the fstat above, but also preventing a pathological case
	 * where there are so many logins that we never reach EOF
	 * before hitting ENOSPC.
	 */
	ret = copy_data(tmpfd, fd, maxsize + (maxsize >> 6));
	/* Must at least fsync, but might as well close, tmpfd before renaming. */
	if (close(tmpfd) < 0) {
		warn("close()");
		goto out;
	}
	if (ret == 0) {
		if (rename(tmppath, wtmppath) < 0) {
			warn("rename(%s, %s)", tmppath, wtmppath);
			ret = 1;
		} else {
			/* We no longer own tmppath. */
			free_tmppath();
		}
	}

out:
	remove_tmpfile();
	if (fd >= 0) {
		/*
		 * If anything goes wrong, we truncate the existing
		 * file to zero size (unless -n). This handles the
		 * cases where the file is corrupt (size%sizeof(struct
		 * utmp) != 0) and where we can't create the temporary
		 * copy of the tail due to ENOSPC.
		 */
		if (ret && !no_truncate) {
			if (ftruncate(fd, 0) < 0)
				warn("ftruncate()");
		}
		if (close(fd) < 0)
			warn("close()");
	}
	return ret;
}

static void
usage(int e)
{
	printf("Usage: %s [-n] [-s SIZE] [wtmpfile]\n", program_invocation_short_name);
	printf("defaults: size=%d, wtmpfile=%s\n", DEFAULT_MAXSIZE, DEFAULT_WTMPFILE);
	printf("-n: do not truncate the existing file on error\n");
	exit(e);
}


static void
parse_options(int argc, char *argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, "hns:")) != -1) {
		switch (opt) {
		case 'h':
			usage(0);
		case '?':
			usage(1);
		case 's':
			maxsize = strtoul(optarg, NULL, 0);
			break;
		case 'n':
			no_truncate = 1;
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	const char *wtmpfile = DEFAULT_WTMPFILE;

	parse_options(argc, argv);
	argc -= optind;
	argv += optind;
	if (argc > 0)
		wtmpfile = argv[0];
	return trim_wtmp(wtmpfile);
}
