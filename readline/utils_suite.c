#include "ft_readline.h"

int		hexvalue(int c)
{
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && (c) <= 'F')
		return (c - 'A' + 10);
	else
		return (c - '0');
}

int	ismetachar(union u_buffer c)
{
	return (c.buf[0] == 27 && c.buf[1] != 0);
}

int	isprintchr(int c)
{
	return (c >= 32 && c <= 126);
}

int	isstdkey(int c)
{
	return (c > 0 && c <= 127);
}

int	isctrlkey(union u_buffer c)
{
	return (c.buf[0] == 27 && c.buf[1] == 91);
}
