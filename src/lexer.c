/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 17:04:12 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/10 18:00:03 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*g_tokval[NB_TOKEN] = {
	[SEMI] = ";",
	[OR_IF] = "||",
	[PIPE] = "|",
	[AND_IF] = "&&",
	[GREATAND] = ">&",
	[LESSAND] = "<&",
	[ANDGREAT] = "&>",
	[AND] = "&",
	[DGREAT] = ">>",
	[DLESSDASH] = "<<-",
	[DLESS] = "<<",
	[GREAT] = ">",
	[LESS] = "<",
	[NEWLINE] = "\n",
	[IO_NB] = NULL,
	[WORD] = NULL,
	[NONE] = NULL
};

static t_token	*get_next_token(const char *str, size_t *i, int prevtype)
{
	t_token	*token;
	size_t	t;

	t = 0;
	while (g_tokval[t]
		&& ft_strncmp(&str[*i], g_tokval[t], ft_strlen(g_tokval[t])))
		++t;
	if (!g_tokval[t])
		token = get_word(str, i, prevtype);
	else
	{
		token = ft_memalloc(sizeof(t_token));
		token->type = t;
		*i += ft_strlen(g_tokval[t]);
	}
	return (token);
}

static int		add_token_to_list(t_token *token, t_list **lst)
{
	t_list	*new;
	t_list	*tmp;

	tmp = *lst;
	new = ft_memalloc(sizeof(t_list));
	if (!new)
		return (FAILURE);
	new->content = token;
	if (!*lst)
		*lst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}

t_list			*list_tokens(const char *input)
{
	t_list	*lst;
	t_token	*token;
	size_t	i;
	int		prevtype;

	i = 0;
	lst = NULL;
	prevtype = WORD;
	while (input[i])
	{
		token = get_next_token(input, &i, prevtype);
		if (token->type == DLESSDASH)
			token->type = DLESS;
		prevtype = token->type;
		add_token_to_list(token, &lst);
		while (input[i] != '\n' && ft_isspace(input[i]))
			++i;
	}
	return (lst);
}

t_list			*lexer(const char *input)
{
	t_list	*lst;

	while (ft_isblank(*input))
		++input;
	if (!input)
		return (NULL);
	lst = list_tokens(input);
	if (lst)
		check_alias(&lst, TRUE);
	if (lst && get_tokentype(ft_lst_last(lst)) != NEWLINE)
		ft_lstdel(&lst, del);
	return (lst);
}
