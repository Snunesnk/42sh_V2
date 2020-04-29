/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:30 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/29 19:45:39 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

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
