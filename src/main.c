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

static void	del(void *content, size_t content_size)
{
	(void)content_size;
	ft_strdel(&((t_token*)(content))->value);
	free(content);
}


int			main(int argc, char **argv)
{
	int		index;
	uint64_t	buffer[BUF_SIZE];
	t_list		*lst;
	char		*input;

	(void)argc;
	(void)argv;
	if (init_shell())
		return (EXIT_FAILURE);
/*	while (ft_printf("$> ") && get_stdin(&input) >= 0)
*/	if (ft_printf("$> ") && get_stdin(&input) >= 0)
	{
		lst = NULL;
		index = 0;
		ft_bzero(&buffer, sizeof(buffer));
		lexer(input, &lst);
		debug(lst);
		if (parser(lst, buffer, index) == EXIT_FAILURE)
			ft_putendl_fd("\nParse error", 2);
		else
		{
		/*	ft_putendl("\nOK"); */
			launch_all_jobs(lst); /* to capture */
		}
		ft_lstdel(&lst, del);
		ft_strdel(&input);
	}
	return (EXIT_SUCCESS);
}
