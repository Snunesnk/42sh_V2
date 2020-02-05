#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "libft.h"
#include "ft_errno.h"
#include "builtins.h"

int	launch_builtin(t_process *p)
{
	/* Execute the builtin. Retreive return value */
	return builtins_dispatcher(p);
}
