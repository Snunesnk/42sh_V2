/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 17:12:33 by yforeau           #+#    #+#             */
/*   Updated: 2020/05/15 16:56:47 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# define SHELL_QUOTES	"\"\'\\"

# define NO_QUOTE	0x00
# define DQUOTE		0x01
# define SQUOTE		0x02
# define BSQUOTE	0x04
# define FULL_QUOTE	0x07

int		get_qmode(int qmode, char c);
char	*ft_strstr_qmode(const char *str, const char *to_find,
			int allowed_qmodes, int *qmode);
int		rm_quotes(char **str, int old_qmode);
int		has_unquoted_spec_chars(const char *str, const char *spec);
int		get_str_qmode(int qmode, char *s);

#endif
