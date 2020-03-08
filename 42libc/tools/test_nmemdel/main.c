#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "libft.h"

int main(void)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;
	char	*s6;
	char	*s7;
	char	*s8;

	s1 = strdup("1st line\n");
	s2 = strdup("2nd line\n");
	s3 = strdup("3rd line\n");
	s4 = strdup("4th line\n");
	s5 = strdup("5th line\n");
	s6 = strdup("6th line\n");
	s7 = strdup("7th line\n");
	s8 = strdup("8th line\n");

	fprintf(stderr, "Before del:\n%s\n", s1);
	
	ft_nmemdel(8, (void**)&s1, (void**)&s2, (void**)&s3, (void**)&s4, (void**)&s5, (void**)&s6, (void**)&s7, (void**)&s8);
	fprintf(stderr, "After del:\n%s\n", s8);

	return (0);
}
