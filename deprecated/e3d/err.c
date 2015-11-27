#include "err.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

extern char *itoa(int, char *, int);

void err(int eval, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}

void errx(int eval, const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}

void warn(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}

void warnx(const char *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}

void verr(int eval, const char *fmt, va_list args)
{
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}

void verrx(int eval, const char *fmt, va_list args)
{
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}

void vwarn(const char *fmt, va_list args)
{
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}

void vwarnx(const char *fmt, va_list args)
{
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);

	abort();
}