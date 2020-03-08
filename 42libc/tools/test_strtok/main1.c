#include <stdio.h>
#include <string.h>

#include "libft.h"
int main ()
{
  char str[] ="	echo ok 	 ;does not  ok 		";
  char str2[] ="- This,   a .sample string.";
  char * pch;
  char *delim;

  delim = " \t\f\n";
  printf ("\n>>Libc\n");
  pch = strtok(str,delim);
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok(NULL, delim);
  }
  pch = strtok(str2,delim);
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok(NULL, delim);
  }
  return 0;
}
