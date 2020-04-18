/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_job3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:30 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/18 23:31:43 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*dup_token_value(char **argv, int i, t_list *lst)
{
	char	**wt;

	if (!(argv[i] = get_tokvalue(lst)))
	{
		wt = argv;
		while (*wt)
			free(*wt++);
		free(argv);
		return (NULL);
	}
	return (argv[i]);
}
