/* See LICENSE file for copyright and license details. */
#include "arg.h"

#define UTF8_POINT(c) (((c) & 0xc0) != 0x80)
#define LEN(x) (sizeof (x) / sizeof *(x))

extern char *argv0;

char *agetcwd(void);
void apathmax(char **, long *);
void devtotty(int, int *, int *);
void enprintf(int, const char *, ...);
void eprintf(const char *, ...);
long estrtol(const char *, int);
void putword(const char *);
void recurse(const char *, void (*)(const char *));
char *ttytostr(int, int);
