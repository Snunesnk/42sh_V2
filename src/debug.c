/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:31:26 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 16:33:49 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
/*
char	*token_tab[NB_TOKEN] =
{
	[OR_IF] = "OR_IF",
	[PIPE] = "PIPE",
	[AND_IF] = "AND_IF",
	[AND] = "AND",
	[GREATAND] = "GREATAND",
	[LESSAND] = "LESSAND",
	[ANDGREAT] = "ANDGREAT",
	[SEMI] = "SEMI",
	[DGREAT] = "DGREAT",
	[DLESS] = "DLESS",
	[DLESSDASH] = "DLESSDASH",
	[GREAT] = "GREAT",
	[LESS] = "LESS",
	[WORD] = "WORD",
	[IO_NB] = "IO_NB",
	[NEWLINE] = "newline",
};*/

char	*token_tab[NB_TOKEN] =
{
	[OR_IF] = "||",
	[PIPE] = "|",
	[AND_IF] = "&&",
	[AND] = "&",
	[GREATAND] = ">&",
	[LESSAND] = "<&",
	[ANDGREAT] = "&>",
	[SEMI] = ";",
	[DGREAT] = ">>",
	[DLESS] = "<<",
	[DLESSDASH] = "<<-",
	[GREAT] = ">",
	[LESS] = "<",
	[WORD] = "WORD",
	[IO_NB] = "io_nb",
	[NEWLINE] = "newline",
};

static void	printg(t_list *lst, t_list **elem)
{
	char		*print_content;
	char		*tmp;
	size_t		i;

	i = 0;
	print_content = NULL;
	while (i < NB_TOKEN)
	{
		tmp = NULL;
		if (((t_token*)(lst->content))->type == i)
		{
			if (i == WORD || i == IO_NB)
				tmp = ((t_token*)(lst->content))->value;
			ft_asprintf(&print_content, "%s -> [%s]\n", token_tab[i], tmp);
			break ;
		}
		i++;
	}
	*elem = ft_lstnew(print_content, ft_strlen(print_content));
	ft_strdel(&print_content);
}

void		debug(t_list *lst)
{
	ft_lstprint(lst, printg);
}

void		printjob(void)
{
//	return ;
	ft_printf("\nShell pid: %d\n", g_shell_pgid);
	for (t_job *j=g_first_job; j; j = j->next)
	{
		ft_printf("---------\n");
		ft_printf("shell level: %d, j->pid %d, pid %d\n", g_shell_pgid, j->pgid, getpid());
		ft_printf("command: %s\n", j->command);
		ft_printf("----\n");
	}
}
