/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:45:02 by snunes            #+#    #+#             */
/*   Updated: 2020/04/17 13:11:18 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_H
# define FT_GLOB_H

# include <stddef.h>

/*
** gl_pathc count number of matched path so far
** gl_pathv list matched path names
** gl_offs count slots to reserve in gl_pathv
*/
typedef struct	s_glob
{
	size_t	gl_pathc;
	char	**gl_pathv;
	size_t	gl_offs;
}				t_glob;

/*
** Glob flags
*/

/*
**Return on read errors
*/
# define FT_GLOB_ERR			0x001

/*
** Append slash to directories
*/
# define FT_GLOB_MARK			0x002

/*
** Do not sort the result
*/
# define FT_GLOB_NOSORT			0x004

/*
** Reserve slots in gl_pathv
*/
# define FT_GLOB_DOOFFS			0x008

/*
** Return the pattern if no match found
*/
# define FT_GLOB_NOCHECK		0x010

/*
** Append the result to preceding call
*/
# define FT_GLOB_APPEND			0x020

/*
** A '\' is a regular character
*/
# define FT_GLOB_NOESCAPE		0x040

/*
** Allow leading period to be matched
*/
# define FT_GLOB_PERIOD			0x080

/*
** Expand brace expressions
*/
# define FT_GLOB_BRACE			0x100

/*
** Expand tilde
*/
# define FT_GLOB_TILDE			0x200

/*
** TODO: not implemented yet
** Expand tilde but NOMATCH on fail
*/
# define FT_GLOB_TILDE_CHECK	0x400

/*
** Escape special char
*/
# define FT_GLOB_ESCAPE			0x800

/*
** Glob return values
*/

# define FT_GLOB_NOSPACE		0x001
# define FT_GLOB_ABORTED		0x002
# define FT_GLOB_NOMATCH		0x004

int				ft_glob(const char *pattern, int flags, \
			int (*errfunc)(const char *epath, int eerrno), t_glob *pglob);
void			ft_globfree(t_glob *pglob);

#endif
