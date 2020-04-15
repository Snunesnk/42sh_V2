/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/15 12:02:48 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/15 14:33:04 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_readline.h"

static int			lookahead(int curr, int next)
{
	int	i;

	i = 0;
	while (g_parse_table[curr][i] != NONE)
	{
		if (g_parse_table[curr][i] == next)
			return (SUCCESS);
		++i;
	}
	return (FAILURE);
}

static void			merge_list(t_list *lst1, t_list *lst2)
{
	t_list	*tmp;

	if (lst2 != NULL)
	{
		tmp = lst2->next;
		ft_lstdelone(&lst1->next, &del);
		ft_lstdelone(&lst2, &del);
		lst1->next = tmp;
	}
}

static int			subprompt(t_list *lst, enum e_token *enum_tab)
{
	t_list	*new_lst;
	char	*tmp;
	int		ret;

	ret = FAILURE;
	new_lst = NULL;
	if (((t_token*)(lst->content))->type == PIPE
		|| ((t_token*)(lst->content))->type == AND_IF
		|| ((t_token*)(lst->content))->type == OR_IF)
	{
		tmp = ft_readline("> ");
	//	ret = lexer(tmp, &new_lst);
		if (ret == SUCCESS)
		{
			merge_list(lst, new_lst);
			ret = check_next_token(((t_token*)(lst->next->content))->type,
						enum_tab);
		}
		ft_strdel(&tmp);
	}
	return (ret);
}

static void			parse_error(int ret, enum e_token curr_type,
							t_list *lst)
{
	char	*value;

	if (ret == FAILURE)
	{
		value = ((t_token*)(lst->content))->value;
		ft_dprintf(2, "\n21sh: syntax error near unexpected token `%s'%s%s\n",
			g_tokval[curr_type], curr_type < 14 ? "" : " -> ",
			curr_type < 14 ? "" : value);
	}
}

void    init_tab(char **token_tab); /* for debug pupose */

void	print_a_node(int type, int typenext)
// for debug purpose
{
	static char     *token_tab[NB_TOKEN];

	init_tab(token_tab);
	ft_printf("|%s ->", token_tab[type]);
	ft_printf(" %s|\n", token_tab[typenext]);
}

int					parser(t_list *lst)
{
	int	curr_type;
	int	next_type;
	int	ret;

	ret = SUCCESS;
	while (lst->next)
	{
		curr_type = ((t_token*)(lst->content))->type;
		next_type = ((t_token*)(lst->next->content))->type;
		print_a_node(curr_type, next_type); /* DEBUG PAIRS OF TOKENS */
		ret = lookahead(curr_type, next_type);
		if (ret == FAILURE && curr_type == NEWLINE)
		{
			ret = subprompt(lst, enum_tab[prev_type]);
			curr_type = ((t_token*)(lst->next->content))->type;
			lst = lst->next;
			continue ;
		}
		if (ret == FAILURE)
			break;
		lst = lst->next;
	}
	parse_error(ret, curr_type, lst);
	return (ret);
}
