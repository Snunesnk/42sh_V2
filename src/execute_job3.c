/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:30 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/11 19:24:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	**dup_tok_argv(t_list *lst, int argc, char **argv)
{
	int i;

	i = 0;
	while (lst && i < argc)
	{
		if (get_tokentype(lst) == IO_NB)
			lst = lst->next->next->next;
		else if (is_redir_type(get_tokentype(lst)))
			lst = lst->next->next;
		else if (get_tokentype(lst) == WORD)
		{
			if (!dup_token_value(argv, i, lst))
				return (NULL);
			lst = lst->next;
			++i;
		}
		else if (get_tokentype(lst) == PIPE)
			break ;
		else
			lst = lst->next;
	}
	return (argv);
}

int		ft_atoifd(const char *str)
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

char	*dup_token_value(char **argv, int i, t_list *lst)
{
	char	**wt;

	if (!(argv[i] = ft_strdup(get_tokvalue(lst))))
	{
		wt = argv;
		while (*wt)
			free(*wt++);
		free(argv);
		return (NULL);
	}
	return (argv[i]);
}
