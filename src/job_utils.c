/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 17:41:59 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 19:21:41 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void		free_all_processes(t_process *p)
{
	t_process	*next_p;

	while (p)
	{
		next_p = p->next;
		free_process(p);
		p = next_p;
	}
}

static void	free_a_job(t_job *j)
{
	free_all_processes(j->first_process);
	free(j->command);
	free(j);
}

void		free_job(t_job *j)
{
	t_job	*j_next;
	t_job	*tmp;

	if (j == g_first_job)
	{
		free_a_job(j);
		g_first_job = NULL;
	}
	else
	{
		j_next = g_first_job;
		while (j_next && j_next->next)
		{
			if (j_next->next->pgid == j->pgid)
			{
				tmp = j_next->next;
				j_next->next = tmp->next;
				free_a_job(tmp);
				return ;
			}
			j_next = j_next->next;
		}
	}
}

char		*commandline(t_list *lst)
{
	char	*tmp;
	char	*cmd;
	int		type;

	tmp = ft_strdup("");
	cmd = tmp;
	while (lst)
	{
		type = get_tokentype(lst);
		if (type == WORD)
			cmd = ft_strjoin(tmp, get_tokvalue(lst));
		else
			cmd = ft_strjoin(tmp, g_tokval[type]);
		if (lst->next)
		{
			tmp = ft_strjoin(cmd, " ");
			free(cmd);
		}
		lst = lst->next;
	}
	return (cmd);
}

int			ft_atoifd(const char *str)
{
	unsigned long	nbr;
	int				i;
	unsigned short	val;

	i = 0;
	nbr = 0;
	while (str[i] && str[i] > 47 && str[i] < 58)
	{
		val = str[i] ^ ((1 << 5) | (1 << 4));
		if (nbr > nbr * 10 + val)
			return (-1);
		nbr = nbr * 10 + val;
		++i;
	}
	return (nbr);
}
