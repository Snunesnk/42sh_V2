/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 13:01:12 by efischer          #+#    #+#             */
/*   Updated: 2020/03/06 21:05:05 by snunes           ###   ########.fr       */
/*   Updated: 2020/02/12 16:19:31 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static void	init_token_tab(char **token_tab)
{
	token_tab[OR_IF] = "||";
	token_tab[PIPE] = "|";
	token_tab[AND_IF] = "&&";
	token_tab[GREATAND] = ">&";
	token_tab[LESSAND] = "<&";
	token_tab[ANDGREAT] = "&>";
	token_tab[AND] = "&";
	token_tab[DSEMI] = ";;";
	token_tab[SEMI] = ";";
	token_tab[OP_PARENTHESIS] = "(";
	token_tab[CL_PARENTHESIS] = ")";
	token_tab[WHILE_WORD] = "while";
	token_tab[DONE] = "done";
	token_tab[DGREAT] = ">>";
	token_tab[DLESS] = "<<";
	token_tab[DLESSDASH] = "<<-";
	token_tab[GREAT] = ">";
	token_tab[LESS] = "<";
	token_tab[COMMENT] = NULL;
	token_tab[IO_NB] = NULL;
	token_tab[SHELL_VAR] = NULL;
	token_tab[END_OF_FILE] = NULL;
	token_tab[WORD] = NULL;
	token_tab[START] = NULL;
	token_tab[END] = NULL;
	token_tab[NONE] = NULL;
}

static int	is_io_number(const char *str)
{
	size_t	i;

	i = 0;
	if (ft_atoifd(str) < 0)
		return (FALSE);
	else
	{
		while (ft_isdigit(str[i]) == TRUE)
			i++;
		if (str[i] == '>' || str[i] == '<')
			return (TRUE);
	}
	return (FALSE);
}

static void	is_shell_var(char *str, t_token *token)
{
	char	*tmp;
	size_t	len;

	tmp = ft_strchr(str, '=');
	if (tmp != NULL)
	{
		len = tmp - str;
		tmp = ft_strndup(str, len);
		if (ft_isalnum(tmp[len - 1]) == TRUE)
			token->type = SHELL_VAR;
	}
}

static void	get_token_word(const char *str, t_token *token, size_t *len)
{
	char	*tmp;

	tmp = NULL;
	while (str[*len] != '\0' && ft_isblank(str[*len]) == FALSE
		&& ft_ismeta(str[*len]) == FALSE)
	{
		if (str[*len] == '"')
		{
			(*len)++;
			while (str[*len] != '\0' && str[*len] != '"')
			{
				if (str[*len] == '\\' && str[(*len) + 1] == '"')
					(*len)++;
				(*len)++;
			}
		}
		if (str[*len] != '\0')
			(*len)++;
	}
	tmp = ft_strndup(str, *len);
	token->value = ft_strdup(tmp);
	token->type = WORD;
	is_shell_var(tmp, token);
	ft_strdel(&tmp);
	if (token->value == NULL)
		*len = 0;
}

static int	get_word(const char *str, t_token *token, uint64_t *last_token_type)
{
	size_t	len;
	char	*tmp;

	len = 0;
	if (str[len] == '#')
	{
		token->type = COMMENT;
		token->value = ft_strdup(str);
		if (token->value != NULL)
			len = ft_strlen(token->value);
	}
	if (str[len] == '-' && (*last_token_type == GREATAND || *last_token_type == LESSAND))
	{
		token->value = ft_strdup("-");
		token->type = WORD;
		len = 1;
	}
	else if (ft_isdigit(str[len]) == TRUE && is_io_number(str) == TRUE)
	{
		while (ft_isdigit(str[len]) == TRUE)
			len++;
		token->type = IO_NB;
		tmp = ft_strndup(str, len);
		token->value = ft_strdup(tmp);
		ft_strdel(&tmp);
		if (token->value == NULL)
			len = 0;
	}
	else
		get_token_word(str, token, &len);
	return (len);
}

int			get_next_token(const char *str, t_token *token, uint64_t *last_token_type)
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
		pos = get_word(str, token, last_token_type);
	return (pos);
}
