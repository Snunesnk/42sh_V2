/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 16:26:54 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 22:21:02 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static enum e_token	g_delim_tokens[10] = {
	SEMI,
	OR_IF,
	PIPE,
	AND_IF,
	AND,
	NEWLINE,
	NONE
};

static int	is_delim_token(t_token *token)
{
	int	i;

	i = 0;
	while (g_delim_tokens[i] != token->type && g_delim_tokens[i] != NONE)
		++i;
	return (g_delim_tokens[i] == NONE ? FALSE : TRUE);
}

static int	is_valid_alias(t_list *alias_stack, char *token_value,
				char **alias_value)
{
	t_list	*elem;

	if (ft_lst_find(alias_stack, token_value, ft_strcmp))
		return (FALSE);
	if ((elem = get_shell_var(token_value, g_alias)))
	{
		*alias_value = ((t_shell_var *)elem->content)->value;
		return (TRUE);
	}
	return (FALSE);
}

static int	replace_alias(t_list ***lst, t_list *next,
				char *value, int *check)
{
	t_list	*last;
	t_list	*new_tokens;
	int		ret;

	new_tokens = NULL;
	*check = *value && value[ft_strlen(value) - 1] == ' ' ? TRUE : FALSE;
	if ((new_tokens = list_tokens(value))
		&& (ret = check_alias(&new_tokens, TRUE)) == FAILURE)
		ft_lstdel(&new_tokens, del);
	else if (ret == SUCCESS)
	{
		ft_lstdelone(*lst, del);
		if (new_tokens)
		{
			**lst = new_tokens;
			last = ft_lst_last(new_tokens);
			if (*check == FALSE)
				*check = is_delim_token(last->content);
			*lst = &(last->next);
		}
		**lst = next;
	}
	return (ret);
}

static t_list	**get_first_word(t_list **lst)
{
	t_token	*token;

	while (*lst && (token = (*lst)->content)
		&& token->type == WORD
		&& is_valid_assignment(token->value))
		lst = &(*lst)->next;
	return (lst);
}

int			check_alias(t_list **lst, int check)
{
	static t_list	*alias_stack;
	char			*alias_value;
	t_token			*token;
	t_list			cur;
	int				ret;

	ret = SUCCESS;
	lst = get_first_word(lst);
	token = *lst ? (*lst)->content : NULL;
	if (!token)
		return (ret);
	ft_bzero((void *)&cur, sizeof(t_list));
	ft_lstadd(&alias_stack, &cur);
	cur.content = token->value;
	alias_value = NULL;
	if (check == TRUE && token->type == WORD && is_valid_alias(
		alias_stack->next, token->value, &alias_value) == TRUE)
		ret = replace_alias(&lst, (*lst)->next, alias_value, &check);
	else
		check = is_delim_token(token);
	alias_stack = alias_stack->next;
	if (ret == FAILURE)
		return (ret);
	return (check_alias(alias_value ? lst : &(*lst)->next, check));
}
