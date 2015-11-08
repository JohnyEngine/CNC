#include "err.h"
#include <assert.h>
#include <stdio.h>

extern char *itoa(int, char *, int);

void myprintf(const char *fmt, va_list argp)
{
	const char *p;
	int i;
	char *s;
	char fmtbuf[256];

	va_start(argp, fmt);

	for (p = fmt; *p != '\0'; p++)
	{
		if (*p != '%')
		{
			putchar(*p);
			continue;
		}

		switch (*++p)
		{
		case 'c':
			i = va_arg(argp, int);
			putchar(i);
			break;

		case 'd':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 10);
			fputs(s, stdout);
			break;

		case 's':
			s = va_arg(argp, char *);
			fputs(s, stdout);
			break;

		case 'x':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 16);
			fputs(s, stdout);
			break;

		case '%':
			putchar('%');
			break;
		}
	}

	va_end(argp);
}


void err(int eval, const char *fmt, ...)
{
	va_list args;
	myprintf(fmt, args);
}

void errx(int eval, const char *fmt, ...)
{
	va_list args;
	myprintf(fmt, args);
}

void warn(const char *fmt, ...)
{
	va_list args;
	myprintf(fmt, args);
}

void warnx(const char *fmt, ...)
{
	va_list args;
	myprintf(fmt, args);
}

void verr(int eval, const char *fmt, va_list args)
{
	myprintf(fmt, args);
}

void verrx(int eval, const char *fmt, va_list args)
{
	myprintf(fmt, args);
}

void vwarn(const char *fmt, va_list args)
{
	myprintf(fmt, args);
}

void vwarnx(const char *fmt, va_list args)
{
	myprintf(fmt, args);
}