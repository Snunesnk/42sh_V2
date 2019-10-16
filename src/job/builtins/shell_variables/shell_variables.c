/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/16 15:07:54 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"
#include "error.h"
#include "shell_variables.h"

static struct s_shvar	*create_shvar_node(char *value, struct s_shvar *next_content,
						struct s_shvar *next_var, int index)
{
	struct s_shvar	*node;

	node = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->next_content = next_content;
	node->next_var = next_var;
	node->index = index;
	if (index != -1)
		node->isarray |= 1;
	return (node);
}

static int	append_shvar(const char *const name, const char *const content)
{
	struct s_shvar		*tmp;

	tmp = g_shellvar;
	while (tmp->next_var)
	{
		tmp = tmp->next_var;
	}
	tmp->next_var = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!tmp)
		return (e_cannot_allocate_memory);
	tmp = tmp->next_var;
	tmp->value = (char*)name;
	tmp->next_content = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!tmp->next_content)
		return (e_cannot_allocate_memory);
	tmp->next_content->value = (char*)content;
	tmp->index = 0;
	tmp->next_var = NULL;
	return (e_success);
}

static int	assign_lit_value(const char *const name, const char *const value)
{
	/*
		if (!g_shellvar)
			return (init_shvar(name, value));
		else
	*/		return (append_shvar(name, value));
}

static int	assign_array(char *name, char **tokens)
{
	(void)name;
	(void)tokens;
	return (e_success);
}



static int	assign_at_index(char *name, char *content, int index)
{
	struct s_shvar	*tmp;

	tmp = g_shellvar;
	if (!g_shellvar)
	{
		g_shellvar = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
		g_shellvar->value = name;
		g_shellvar->next_var = NULL;
		g_shellvar->next_content = (struct s_shar*)ft_memalloc;
	}

	return (e_success);
}

static int	assign_shvar(char *name, char *content, int index, _Bool has_array_subscript)
{
	char *str;
	char *end;
	char **tok;

	tok = NULL;
	end = content;
	while (*end)
		++end;
	--end;
	if (index == -1)
	{
		if (has_array_subscript)
		{
			*end = '\0';
			++content;
			tok = ft_strsplit(content, ' ');
			if (!tok)
				return (e_cannot_allocate_memory);
			else
				return (assign_array(name, tok));
		}
		else
			return (assign_lit_value(name, content));
	}
	else
	{
		if (has_array_subscript)
		{
			str = name;
			while (*str)
			{
				++str;
			}
			*str = '[';
			while (*str && *str != '=')
				++str;
			if (*str == '=')
				*str = '\0';
			psherror(e_cannot_assign_list_to_array_member, name, e_cmd_type);
			return (e_cannot_assign_list_to_array_member);
		}
		else
		{
			return (e_success);
			assign_at_index(name, content, index);
		}
		
	}
}

int	shellvar_assignement(const char *const str)
{ /* parsing of str containing a shell variable assignement */
	char 	*content;
	char 	*name;
	int		index;
	int		ret;
	_Bool	has_array_subscript;
	
	name = ft_strdup(str);
	if (!name)
		return (e_cannot_allocate_memory);
	content = ft_strstr(name, "=");
	*content = '\0';
	++content;
	index = get_index(name);
	has_array_subscript = contains_array_subscript(content);
	if (index != -1 && has_array_subscript)
	{
		psherror(e_cannot_assign_list_to_array_member, name, e_cmd_type);
		return (e_cannot_assign_list_to_array_member);
	}
	ret = assign_shvar(name, content, index, has_array_subscript);
	return (ret);
}