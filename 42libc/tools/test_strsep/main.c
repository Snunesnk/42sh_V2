#include "libft.h"
#include "ft_getopt.h"
#include "ft_errno.h"
#include "ft_wchar.h"

#include <wchar.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <strings.h>

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	char	*str1a;
	char	*str1b;
	char	*ptr;
	char	*cst;


	str1a  = ft_strdup(" Hello man how are you doing ? this, is ;great! toto");
	str1b  = ft_strdup(" Hello man how are you doing ? this, is ;great! toto");
	ptr = NULL;
	printf("\n>> Libc:\n");
	cst = str1a;
	while ((ptr = strsep(&str1a, " ")))
		printf("%s\n", ptr);
	free(cst);
	printf("\n>> Libft:\n");
	ptr = NULL;
	cst = str1b;
	while ((ptr = ft_strsep(&str1b, " ")))
		printf("%s\n", ptr);
	free(cst);
	str1a  = ft_strdup(" Hello man how are you doing ? this, is ;great! toto");
	str1b  = ft_strdup(" Hello man how are you doing ? this, is ;great! toto");
	ptr = NULL;
	printf("\n>> Libc:\n");
	cst = str1a;
	while ((ptr = strsep(&str1a, " ")))
		printf("%s\n", ptr);
	free(cst);
	printf("\n>> Libft:\n");
	ptr = NULL;
	cst = str1b;
	while ((ptr = ft_strsep(&str1b, " ")))
		printf("%s\n", ptr);
	free(cst);
	return (0);
}
