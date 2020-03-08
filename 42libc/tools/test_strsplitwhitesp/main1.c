#include <stdio.h>
#include <string.h>
#include "libft.h"

/*
void	*malloc(size_t n)
{
	static int i;

	++i;
	if (!(i % 8))
		return (NULL);
	else
		return (valloc(n));
}
*/

int main (void)
{
	char	**tokens;

	tokens = ft_strsplit_whitespaces("\t hello this is not\tthe\fsame\nbut\tworks\nEND");
	ft_print_tables(tokens);
	ft_tabdel(&tokens);
	return 0;
}
