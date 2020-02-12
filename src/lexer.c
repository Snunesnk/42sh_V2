/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 13:59:39 by efischer          #+#    #+#             */
/*   Updated: 2020/02/12 10:46:54 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char		*ft_join_free(char *s1, char *s2, int op)
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

static int		ft_is_space_tab(int c)
{
	int		ret;

	ret = FALSE;
	if (c == ' ' || c == '\t')
		ret = TRUE;
	return (ret);
}

static int	add_token_to_list(t_token *token, t_list **lst)
{
	t_list	*new;
	int		ret;

	ret = SUCCESS;
	new = ft_lstnew(token, sizeof(*token));
	if (new == NULL)
		ret = FAILURE;
	ft_lstaddend(lst, new);
	return (ret);
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

static void	manage_heredoc(t_token *token)
{
	char	*tmp;
	char	*eof;

	eof = ft_strdup(token->value);
	ft_strdel(&token->value);
	while (1)
	{
		ft_printf(">");
		get_stdin(&tmp);
		tmp = ft_join_free(tmp, "\n", 1);
		if (ft_strstr(tmp, eof) != NULL)
		{
			ft_strdel(&tmp);
			break ;
		}
		if (token->value == NULL)
			token->value = ft_strdup(tmp);
		else
			token->value = ft_join_free(token->value, tmp, 3);
	}
}

static void	get_input(char *str)
{
	char	*tmp;

	tmp = NULL;
	while (1)
	{
		ft_printf(">");
		get_stdin(&tmp);
		if (tmp != NULL)
		{
			ft_strcat(str, tmp);
			break ;
		}
	}
}

static int	new_token(char *str, uint64_t *type, size_t *pos, t_list **lst)
{
	int				ret;
	t_token			token;
	static size_t	last_pos;

	ret = SUCCESS;
	ft_bzero(&token, sizeof(token));
	last_pos = *pos;
	*pos += get_next_token(str + *pos, &token);
	if (str[*pos] == '\0' && token.type == PIPE)
		get_input(str);
	else if (*type == DLESS && token.type == WORD)
		manage_heredoc(&token);
	*type = token.type;
	if (token.type != SEMI && token.type != OR_IF && token.type != AND_IF
		&& token.type != AND)
	{
		ret = add_token_to_list(&token, lst);
	}
	if (*pos == last_pos || ret == FAILURE)
		ret = FAILURE;
	return (ret);
}

static int	get_token_list(char *str, size_t *pos, t_list **lst,
							uint64_t *type)
{
	int		ret;

	ret = SUCCESS;
	while (str[*pos] != '\0')
	{
		while (ft_is_space_tab(str[*pos]) == TRUE)
			(*pos)++;
		if (str[*pos] == '\0')
			break ;
		ret = new_token(str, type, pos, lst);
		if (ret == FAILURE)
			break ;
		if (*type == SEMI || *type == OR_IF || *type == AND_IF || *type == AND)
			break ;
	}
	return (ret);
}

static int	get_pipeline(char *str, size_t *pos, t_list **lst,
						uint64_t *type)
{
	int		ret;

	ret = get_token_list(str, pos, lst, type);
	if (ret == SUCCESS)
		ret = border_token_list(lst, END);
	else
		ret = FAILURE;
	return (ret);
}

int			lexer(char *str, t_ast **ast)
{
	int			ret;
	uint64_t	type;
	size_t		pos;
	t_list		*lst;

	pos = 0;
	while (str[pos] != '\0')
	{
		type = NONE;
		lst = NULL;
		while (ft_is_space_tab(str[pos]) == TRUE)
			pos++;
		if (str[pos] != '\0')
		{
			ret = border_token_list(&lst, START);
			if (ret == SUCCESS)
				ret = get_pipeline(str, &pos, &lst, &type);
			build_ast(type, ast, lst);
			if (str[pos] == '\0' && (type == OR_IF || type == AND_IF))
				get_input(str);
		}
	}
	return (ret);
}
