/* See LICENSE file for copyright and license details. */
#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

static void
usage(void)
{
	eprintf("usage: %s filename [args]\n", argv0);
}

int
main(int argc, char *argv[])
{
	char *buf = NULL, *opts = NULL;
	unsigned long blen, plen = 0;
	int i, fd;
	ssize_t n;
	struct stat sb;

	ARGBEGIN {
	default:
		usage();
	} ARGEND;

	if (argc < 1)
		usage();

	fd = open(argv[0], O_RDONLY);
	if (fd < 0)
		eprintf("open %s:", argv[0]);
	if (fstat(fd, &sb) < 0)
		eprintf("stat %s:", argv[0]);
	buf = malloc(sb.st_size);
	if (!buf)
		eprintf("malloc:");
	blen = sb.st_size;

	if ((n = read(fd, buf, blen)) != blen)
		eprintf("read:");

	argc--;
	argv++;

	for (i = 0; i < argc; i++)
		plen += strlen(argv[i]);
	if (plen > 0) {
		plen += argc;
		opts = malloc(plen);
		if (!opts)
			eprintf("malloc:");
		for (i = 0; i < argc; i++) {
			strcat(opts, argv[i]);
			if (i + 1 < argc)
				strcat(opts, " ");
		}
	}

	if (syscall(__NR_init_module, buf, blen, !opts ? "" : opts) < 0)
		eprintf("init_module:");

	free(opts);
	free(buf);
	return 0;
}