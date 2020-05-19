#include "quotes.h"

int		get_str_qmode_set(int qmode, char *s, int quote_set)
{
	while (*s)
		qmode = get_qmode(qmode, *s++) & quote_set;
	return (qmode);
}

int		get_str_qmode(int qmode, char *s)
{
	while (*s)
		qmode = get_qmode(qmode, *s++);
	return (qmode);
}
