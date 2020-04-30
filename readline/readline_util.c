/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:01:24 by snunes            #+#    #+#             */
/*   Updated: 2020/04/30 20:16:29 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"
#include "quotes.h"

char	*get_quote(int *qmode, char *input)
{
	char	*compl;
	char	*new;

	while (*qmode != NO_QUOTE)
	{
		*qmode &= ~BSQUOTE;
		compl = readline_loop("> ", qmode);
		new = ft_strjoin(input, compl);
		free(input);
		free(compl);
		input = new;
	}
	return (input);
}
