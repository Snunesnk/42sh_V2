/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 13:20:50 by snunes            #+#    #+#             */
/*   Updated: 2020/04/10 13:22:20 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GLOB_INTERNAL_H
# define FT_GLOB_INTERNAL_H

# include "ft_glob.h"
# include "libft.h"

typedef struct	s_glob_internal
{
	int	(*errf)(const char *epath, int eerrno);
	int	fnmflags;
	int	flags;
	int	ret;
}				t_glob_internal;

typedef struct	s_file_data
{
	const char	*name;
	const char	*pathname;
	int			dir;
}				t_file_data;

enum	e_pathtype {GL_NONE, GL_END, GL_RAWPATH, GL_WILDCARD};

# define META_CHARS	"\\{?[*"

/*
** File utils
*/

void			set_read_error(t_glob_internal *gl,
				const char *pathname, int err);
char			*add_to_path(const char *path, const char *to_add);
int				is_dir(const char *pathname, t_glob_internal *gl);
t_file_data		*init_file(t_file_data *dest, const char *path,
				const char *name, t_glob_internal *gl);
t_list			*add_file_lst(const char **file, int add_slash,
				t_glob_internal *gl);

/*
** Build patterns
*/

t_list			*build_patterns(const char *pattern, t_glob_internal *gl);
void			expand_pattern_list(t_list **pattern_list,
				t_glob_internal *gl);

/*
** Build brace patterns
*/

const char		*go_to_closing_curl(const char *pattern,
				t_glob_internal *gl);
const char		*get_brace_expression(t_glob_internal *gl,
				const char *pattern, const char **start,
				const char **end);
t_list			*build_brace_patterns(const char *start, const char *end,
				const char *exp, t_glob_internal *gl);

/*
** Match
*/

void			del_match(void *string, size_t size);
t_list			*add_slash(const char *path, t_glob_internal *gl);
t_list			*find_file(const char *path, const char *cur_pattern,
				int only_dir, t_glob_internal *gl);
t_list			*match_files(const char *path, const char *cur_pattern,
				int only_dir, t_glob_internal *gl);
t_list			*match_next_pattern(t_glob_internal *gl,
				const char *pattern, t_list *match);
int				store_match_list(t_glob *pglob, t_glob_internal *gl,
				t_list *match);
int				void_strcmp(void *s1, void *s2);

/*
** Internal functions
*/

void			*check_mem(t_glob_internal *gl, void *mem);
enum e_pathtype	slash_path(const char **pattern,
				const char **cur_pattern, t_glob_internal *gl);
t_list			*ft_glob_internal(t_glob_internal *gl,
				const char *pattern, const char *path);

#endif
