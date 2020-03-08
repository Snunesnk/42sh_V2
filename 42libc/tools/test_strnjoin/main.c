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
	char	*final;

	final = ft_strnjoin(7, "Hello ", "my name ", "is ", "Valentine ", "I ", "code", "\n");
	printf("%s\n", final);
	ft_memdel((void**)&final);	
	return (0);
}
