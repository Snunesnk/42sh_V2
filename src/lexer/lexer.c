/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:08:45 by efischer          #+#    #+#             */
/*   Updated: 2019/12/04 16:50:04 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int		ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

static void	init_token_tab(char **token_tab)
{
	token_tab[PIPE] = "|";
	token_tab[AND] = "&";
	token_tab[SEMICOLON] = ";";
	token_tab[OP_BRACKET] = "(";
	token_tab[CL_BRACKET] = ")";
	token_tab[R_DB_REDIR] = ">>";
	token_tab[L_DB_REDIR] = "<<";
	token_tab[R_REDIR] = ">";
	token_tab[L_REDIR] = "<";
	token_tab[COMMENT] = NULL;
	token_tab[WORD] = NULL;
	token_tab[START] = NULL;
	token_tab[END] = NULL;
}

static int	get_word(const char *str, t_token *token)
{
	size_t	len;

	len = 0;
	if (str[len] == '#')
	{
		token->type = COMMENT;
		token->value = ft_strdup(str);
		if (token->value != NULL)
			len = ft_strlen(token->value);
	}
	else
	{
		while (ft_isblank(str[len]) == FALSE && ft_ismeta(str[len]) == FALSE
				&& str[len] != '\0')
		{
			len++;
		}
		token->type = WORD;
		token->value = ft_strndup(str, len);
		if (token->value == NULL)
			len = 0;
	}
	return (len);
}

static int	get_next_token(const char *str, t_token *token)
{
	char	*token_tab[NB_TOKEN];
	size_t	token_index;
	size_t	pos;

	pos = 0;
	token_index = 0;
	init_token_tab(token_tab);
	while (token_index < NB_TOKEN)
	{
		if (ft_strnequ(str, token_tab[token_index],
					ft_strlen(token_tab[token_index])) == TRUE)
		{
			token->type = token_index;
			pos = ft_strlen(token_tab[token_index]);
			break ;
		}
		token_index++;
	}
	if (token_index == NB_TOKEN)
		pos = get_word(str, token);
	return (pos);
}

static int	add_token_to_list(t_token *token, t_list **lst)
{
	t_list	*new;
	int		ret;

	new = ft_lstnew(token, sizeof(*token));
	if (new == NULL)
		return(EXIT_FAILURE);
	ft_lstaddend(lst, new);
	return (EXIT_SUCCESS);
}

static int	border_token_list(t_list **lst, uint64_t token_type)
{
	t_token	token;
	int		ret;

	ft_bzero(&token, sizeof(token));
	token.type = token_type;
	ret = add_token_to_list(&token, lst);
	return (ret);
}

static int	get_token_list(const char *str, t_list **lst)
{
	t_token	token;
	size_t	last_pos;
	size_t	pos;
	int		ret;

	pos = 0;
	while (str[pos] != '\0')
	{
		while (ft_isblank(str[pos]) == TRUE)
			pos++;
		if (str[pos] == '\0')
			break ;
		ft_bzero(&token, sizeof(token));
		last_pos = pos;
		pos += get_next_token(str + pos, &token);
		ret = add_token_to_list(&token, lst);
		if (pos == last_pos || ret == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			lexer(const char *str, t_list **lst)
{
	int		ret;

	ret = border_token_list(lst, START);
	if (ret == EXIT_SUCCESS)
	{
		ret = get_token_list(str, lst);
		if (ret == EXIT_SUCCESS)
			ret = border_token_list(lst, END);
	}
	return (ret);
}
