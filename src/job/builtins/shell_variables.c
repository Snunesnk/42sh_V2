/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variables.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:10:04 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/15 13:17:26 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "shell_variables.h"
#include "error.h"

struct s_shvar	*g_shellvar = NULL;

int	init_shvar(const char *name, const char *const content)
{
	extern struct s_shvar	*g_shellvar;
	
	g_shellvar = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!g_shellvar)
	{
		return (e_cannot_allocate_memory);
	}
	g_shellvar->value = (char*)name;
	g_shellvar->next_content = (struct s_shvar*)ft_memalloc(sizeof(struct s_shvar));
	if (!g_shellvar->next_content)
	{
		return (e_cannot_allocate_memory);
	}
	g_shellvar->next_content->value = (char*)content;
	g_shellvar->index = 0;
	g_shellvar->next_var = NULL;
	return (e_success);
}

static int	append_shvar(const char *const name, const char *const content)
{
	extern struct s_shvar	*g_shellvar;
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

static int	assign_shvar(char *name, char *content)
{
	char *end;
	char **tok;

	tok = NULL;
	end = content;
	while (*end)
		++end;
	--end;
	if (*end == ')' && *content == '(')
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

static int	name_index(char *name)
{
	while (*name && *name != '[')
		++name;
	if (*name != '[')
		  return (-1);
	else
	{
		*name = '\0';
		++name;
		return (ft_atoi(name)); /* should be a special atoi, maybe a ft_atoull63bits() */
	}
}

int	shellvar_assignement_parsing(const char *const str)
{
	int		ret;
	int		index;
	char 	*content;
	char 	*name;
	
	name = ft_strdup(str);
	if (!name)
		return (e_cannot_allocate_memory);
	content = ft_strstr(name, "=");
	*content = '\0';
	++content;
	index = name_index(name);
	if (index == -1)
		ret = assign_shvar(name, content);
	else
	{
		/* here case in must input at a certain index */
		return (e_success);
	}
	return (ret);
}