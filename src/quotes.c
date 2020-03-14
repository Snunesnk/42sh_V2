#include "libft.h"
#include "shell.h"
#include "error.h"

/* Return 1 if index is without quotes or has \ before, i.e. inihibited */
char	*move_to_next_inhibitor_boundary(char *s)
{
	char	backq;
	size_t	i;

	i = 0;
	baskq = 0;
	while (s[i] && i < index)
	{
		if (s[i] == '\'')
			backq ^= '\'';
	}
	return (backq);
}
