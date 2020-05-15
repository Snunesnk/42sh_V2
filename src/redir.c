/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 15:31:03 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/15 19:53:18 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "shell.h"
#include "quotes.h"

int				expand_filename(t_redirection *r, char **word)
{
	if (treat_single_exp(word, 1))
		r->error = e_bad_substitution;
	else if (rm_quotes(word, NO_QUOTE))
		r->error = e_cannot_allocate_memory;
	else
		return (0);
	return (1);
}

int				has_redirections(int type)
{
	return (type == IO_NB
		|| type == LESS
		|| type == GREAT
		|| type == DLESS
		|| type == DGREAT
		|| type == ANDGREAT
		|| type == LESSAND
		|| type == GREATAND);
}

int				ha(char *str)
{
	int	i;

	if ((i = ft_strlen(str)) > 0)
		--i;
	if (str[i] == '-')
	{
		str[i] = '\0';
		return (1);
	}
	else
		return (0);
}

t_redirection	*set_redirection(t_list **lst, int io_nb)
{
	int	type;

	type = get_tokentype(*lst);
	if (type == GREAT)
		return (type_great_redirection(lst, io_nb));
	else if (type == DGREAT)
		return (type_dgreat_redirection(lst, io_nb));
	else if (type == LESS)
		return (type_less_redirection(lst, io_nb));
	else if (type == DLESS)
		return (type_dless_redirection(lst, io_nb));
	else if (type == GREATAND)
		return (type_greatand_redirection(lst, io_nb));
	else if (type == LESSAND)
		return (type_lessand_redirection(lst, io_nb));
	else if (type == ANDGREAT)
		return (type_andgreat_redirection(lst, io_nb));
	return (NULL);
}
