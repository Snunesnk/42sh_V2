/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_char_classes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:25:18 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 13:25:23 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"
#include "g_char_classes.h"

const t_char_class	g_char_classes[] =
{
	{"alnum", ft_fnm_is_alnum},
	{"digit", ft_fnm_is_digit},
	{"punct", ft_fnm_is_punct},
	{"alpha", ft_fnm_is_alpha},
	{"graph", ft_fnm_is_graph},
	{"space", ft_fnm_is_space},
	{"blank", ft_fnm_is_blank},
	{"lower", ft_fnm_is_lower},
	{"upper", ft_fnm_is_upper},
	{"cntrl", ft_fnm_is_cntrl},
	{"print", ft_fnm_is_print},
	{"xdigit", ft_fnm_is_xdigit},
	{NULL, NULL}
};

t_char_class_fct	get_char_class_fct(const char *name, size_t len)
{
	int	i;

	i = -1;
	while (g_char_classes[++i].name)
	{
		if (ft_strlen(g_char_classes[i].name) == len
			&& !ft_strncmp(name, g_char_classes[i].name, len))
			return (g_char_classes[i].f);
	}
	return (NULL);
}
