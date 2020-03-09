#include "ft_readline.h"

int	mvctrlkey(union u_buffer c)
{
	return (c.buf[2] == 49 && c.buf[3] == 59 && c.buf[4] == 53);
}

int	enter_rc(union u_buffer c)
{
	return (c.buf[0] == 13 && c.buf[1] == 0);
}
