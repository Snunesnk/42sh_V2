/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:44 by efischer          #+#    #+#             */
/*   Updated: 2019/12/04 16:43:13 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char	*ft_join_free(char *s1, char *s2, int op)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (op == 1)
		ft_strdel(&s1);
	else if (op == 2)
		ft_strdel(&s2);
	else
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
	}
	return (str);
}


static void	del(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_token*)(content))->value);
	free(content);
}

static char	*tab_to_str(char **av)
{
	char	*str;
	size_t	i;

	i = 0;
	str = NULL;
	while (av[i] != NULL)
	{
		str = ft_join_free(str, av[i], 1);
		if (str == NULL)
			break ;
		i++;
	}
	return (str);
}

int			main(int ac, char **av)
{
	uint64_t	buffer[BUF_SIZE];
	size_t		index;
	t_list		*lst;
	char		*str;

	lst = NULL;
	if (ac >= 2)
	{
		index = 0;
		ft_bzero(&buffer, sizeof(buffer));
		str = tab_to_str(av + 1);
		if (str != NULL)
		{
			lexer(str, &lst);
			debug(lst);
			if (parser(lst, buffer, index) == FAILURE)
				ft_putendl_fd("\nParse error", 2);
			else
				ft_putendl("\nOK");
		}
		ft_lstdel(&lst, del);
		ft_strdel(&str);
	}
	return (EXIT_SUCCESS);
}
