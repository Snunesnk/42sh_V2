#include <stdio.h>
#include <string.h>
#include "libft.h"

/*
void	*malloc(size_t n)
{
	static int i;

	++i;
	if (!(i % 9))
		return (NULL);
	else
		return (valloc(n));
}
*/

int main ()
{
  char str[] = "\t - This\t, a \fsample\n string. ";
  char str2[] = " ";
  char str3[] = "";
  char str4[] = "Hello";
  char str5[] = " \tHello";
  char str6[] = "\0Hello";
  char str7[] = "Hello \t\t\t\t\t\t\t";
  char	**tab;

  printf ("\n|%s|\n", str);
  tab = ft_strsplit_whitespaces(str);
  ft_print_tables(tab);
  ft_tabdel(&tab);
  printf ("\n|%s|\n", str2);
  tab = ft_strsplit_whitespaces(str2);
  ft_print_tables(tab);
  ft_tabdel(&tab);
  printf ("\n|%s|\n", str3);
  tab = ft_strsplit_whitespaces(str3);
  ft_print_tables(tab);
  ft_tabdel(&tab);
  printf ("\n|%s|\n", str4);
  tab = ft_strsplit_whitespaces(str4);
  ft_print_tables(tab);
  ft_tabdel(&tab);
  printf ("\n|%s|\n", str5);
  tab = ft_strsplit_whitespaces(str5);
  ft_print_tables(tab);
  ft_tabdel(&tab);
  printf ("\n|%s|\n", str6);
  tab = ft_strsplit_whitespaces(str6);
  ft_print_tables(tab);
  ft_tabdel(&tab);
  printf ("\n|%s|\n", str7);
  tab = ft_strsplit_whitespaces(str7);
  ft_print_tables(tab);
  ft_tabdel(&tab);
  return 0;
}
