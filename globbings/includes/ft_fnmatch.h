/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fnmatch.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 12:46:18 by yforeau           #+#    #+#             */
/*   Updated: 2020/02/23 15:34:59 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FNMATCH_H
# define FT_FNMATCH_H

/*
** FT_FNM flags can be set by the user
*/

# define FT_FNM_NOESCAPE	0x01	/* Treat a '\' as a regular character */
# define FT_FNM_PATHNAME	0x02	/* A '/' must be explicitly matched */
# define FT_FNM_PERIOD		0x04	/* A leading '.' needs explicit match */

/* TODO: NOT IMPLEMENTED YET */
# define FT_FNM_CASEFOLD	0x08	/* Make fnmatch case insensitive (GNU) */

# define FT_FNM_NOMATCH		0x01	/* To be returned if there is no match */

int	ft_fnmatch(const char *pattern, const char *string, int flags);

#endif
