/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_lexer_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:06:39 by efischer          #+#    #+#             */
/*   Updated: 2020/03/10 11:20:32 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		launch_lexer_parser(char *input, t_ast **ast)
{
	t_list	*lst;
	int		ret;

	lst = NULL;
	ret = lexer(input, &lst);
	if (ret == SUCCESS)
	{
		ret = parser(lst);
		if (ret == SUCCESS)
			ret = build_ast(ast, lst);
	}
	return (ret);
}
