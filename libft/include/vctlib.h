/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vctlib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 12:13:44 by efischer          #+#    #+#             */
/*   Updated: 2019/10/29 16:14:28 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VCTLIB_H
# define VCTLIB_H

# include "libft.h"

# define	DFL_SIZE 64
# define	DFL_SCALE 16

typedef struct	s_vector
{
	char	*str;
	size_t	len;
	size_t	size;
	size_t	scale;
}				t_vector;

t_vector	*vct_newstr(const char *str);
t_vector	*vct_new(void);
int			vct_resize(t_vector	*vct);
int			vct_addstr(const char *str, t_vector *vct);
int			vct_pushstr(const char *str, t_vector *vct);
void		vct_clear(t_vector *vct);
int			vct_reset(t_vector *vct);
int			vct_addchar(const char c, t_vector *vct);
int			vct_pushchar(const char c, t_vector *vct);
int			vct_insertchar(const char c, const size_t pos, t_vector *vct);
int			vct_insertstr(const char *str, const size_t pos, t_vector *vct);
void		vct_del(t_vector *vct);
void		vct_dellastchar(t_vector *vct);
void		vct_delfirstchar(t_vector *vct);
void		vct_delchar(t_vector *vct, size_t pos);
void		vct_delnchar(t_vector *vct, size_t pos, size_t n);
int			vct_replace(t_vector *vct, char *occurence, char *replace);

#endif
