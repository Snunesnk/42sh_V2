/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:46:18 by yforeau           #+#    #+#             */
/*   Updated: 2020/04/10 12:42:10 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FNMATCH_H
# define FT_FNMATCH_H

/*
** FT_FNM flags can be set by the user
*/

/*
**Treat a '\' as a regular character
*/
# define FT_FNM_NOESCAPE	0x01

/*
** A '/' must be explicitly matched
*/
# define FT_FNM_PATHNAME	0x02

/*
** A leading '.' needs explicit match
*/
# define FT_FNM_PERIOD		0x04

/*
** TODO: NOT IMPLEMENTED YET, make fnmatch case insensitive
*/
# define FT_FNM_CASEFOLD	0x08

/*
** To be returned if there is no matche
*/
# define FT_FNM_NOMATCH		0x01

int	ft_fnmatch(const char *pattern, const char *string, int flags);

#endif
