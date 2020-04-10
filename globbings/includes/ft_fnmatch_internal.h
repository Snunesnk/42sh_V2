/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch_internal.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:17:04 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 13:20:36 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FNMATCH_INTERNAL_H
# define FT_FNMATCH_INTERNAL_H

/*
** Get the external flags only
*/
# define FT_FNM_EXTMASK			0x0f

/*
** Skip the current char (useful for '\')
*/
# define FT_IFNM_SKIP			0x10

/*
** The current character is not special
*/
# define FT_IFNM_FORCE_REG		0x20

/*
** The current dot if any, is leading
*/
# define FT_IFNM_LEADING_PERIOD	0x40

/*
** For case insensitive matching
*/
# define CASE_OFFSET		32

# define BRACK_SPEC_CHARS	"\\!:-]"
# define GLOB_SPEC_CHARS	"\\?[*"

typedef struct	s_flags
{
	int	cur;
	int	next;
}				t_flags;

int				set_flags(char pattern, char string, t_flags *flags);
int				match_star(const char **pattern, const char **string, \
		t_flags *flags);
int				explicit_match(char string, t_flags *flags);
int				match_qmark(const char **pattern, const char **string, \
		t_flags *flags);
int				match_reg(const char **pattern, const char **string);
int				match_brack(const char **pattern, const char **string, \
		t_flags *flags);
int				ft_fnmatch_internal(const char *pattern, const char *string,\
		t_flags flags);

#endif
