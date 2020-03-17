#include <glob.h> //TEMP
#include "libft.h"
#include "error.h"
#include "shell.h"

static int	replace_pattern(t_process *p, int i, glob_t *gl)
{
	int	new_argc;
	char	**new_argv;

	ft_memdel((void **)p->argv + i);
	if (gl->gl_pathc > 1)
	{
		new_argc = p->argc + gl->gl_pathc - 1;
		if (!(new_argv = ft_memalloc((new_argc + 1) * sizeof(char *))))
			return (e_cannot_allocate_memory);
		ft_memcpy(new_argv, p->argv, i * sizeof(char *));
		ft_memcpy(new_argv + i + gl->gl_pathc, p->argv + i + 1,
			(p->argc - i - 1) * sizeof(char *));
		ft_memdel((void **)&p->argv);
		p->argv = new_argv;
		p->argc = new_argc;
	}
	ft_memcpy(p->argv + i, gl->gl_pathv, gl->gl_pathc * sizeof(char *));
	ft_bzero(gl->gl_pathv, gl->gl_pathc * sizeof(char *));
	globfree(gl);
	return (e_success);
}

int		pathname_expansion(t_process *p, int i)
{
	glob_t	gl;
	int	ret;

	ft_bzero(&gl, sizeof(glob_t));
	ret = glob(p->argv[i], GLOB_NOCHECK, NULL, &gl); //TODO: ADD FT_GLOB_BRACE to flags
	//TODO: find a way not to copy the string each time and to use GLOB_APPEND
	//instead of copying the entire argv each time
	if (!ret)
		return (replace_pattern(p, i, &gl));
	else if (ret == GLOB_NOSPACE)
		return (e_cannot_allocate_memory);
	else if (ret == GLOB_ABORTED)
		return (e_system_call_error);
	return (e_success);
}
