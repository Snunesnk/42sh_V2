/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:01:12 by efischer          #+#    #+#             */
/*   Updated: 2019/12/18 15:42:11 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vctlib.h"
#include "shell.h"

#define TRUE 1
#define FALSE 0

static int		ft_isblank(int c)
{
	return (c == ' ' || c == '\t');
}

static int		ft_ismeta(int c)
{
	int		ret;

	ret = FALSE;
	if (c == '|' || c == '&' || c == ';' || c == '(' || c == ')'
		|| c == '<' || c == '>')
	{
		ret = TRUE;
	}
	return (ret);
}

static void	init_token_tab(char **token_tab)
{
	token_tab[OR_IF] = "||";
	token_tab[PIPE] = "|";
	token_tab[AND_IF] = "&&";
	token_tab[AND] = "&";
	token_tab[DSEMI] = ";;";
	token_tab[SEMI] = ";";
	token_tab[OP_PARENTHESIS] = "(";
	token_tab[CL_PARENTHESIS] = ")";
	token_tab[WHILE_WORD] = "while";
	token_tab[DONE] = "done";
	token_tab[DGREAT] = ">>";
	token_tab[DLESS] = "<<";
	token_tab[GREAT] = ">";
	token_tab[LESS] = "<";
	token_tab[COMMENT] = NULL;
	token_tab[IO_NB] = NULL;
	token_tab[WORD] = NULL;
	token_tab[START] = NULL;
	token_tab[END] = NULL;
}

static int	is_io_number(const char *str)
{
	size_t	i;
	int		ret;

	i = 0;
	ret = FALSE;
	while (ft_isdigit(str[i]) == TRUE)
		i++;
	while (ft_isblank(str[i]) == TRUE)
		i++;
	if (str[i] == '>' || str[i] == '<')
		ret = TRUE;
	return (ret);
}

static int	get_word(const char *str, t_token *token)
{
	size_t	len;
	char	*tmp;

	len = 0;
	if (str[len] == '#')
	{
		token->type = COMMENT;
		token->value = vct_newstr(str);
		if (token->value != NULL)
			len = ft_strlen(token->value->str);
	}
	else if (ft_isdigit(str[len]) == TRUE && is_io_number(str) == TRUE)
	{
		while (ft_isdigit(str[len]) == TRUE)
			len++;
		token->type = IO_NB;
		tmp = ft_strndup(str, len);
		ft_printf("tmp: %s\n", tmp);
		token->value = vct_newstr(tmp);
		ft_strdel(&tmp);
		if (token->value == NULL)
			len = 0;
	}
	else
	{
		while (ft_isblank(str[len]) == FALSE && ft_ismeta(str[len]) == FALSE
				&& str[len] != '\0')
		{
			if (str[len] == '"')
			{
				len++;
				while (str[len] != '"' && str[len] != '\0')
				{
					if (str[len] == '\\' && str[len + 1] == '"')
						len++;
					len++;
				}
			}
			if (str[len] != '\0')
				len++;
		}
		token->type = WORD;
		tmp = ft_strndup(str, len);
		token->value = vct_newstr(tmp);
		ft_strdel(&tmp);
		if (token->value == NULL)
			len = 0;
	}
	return (len);
}

int			get_next_token(const char *str, t_token *token)
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
