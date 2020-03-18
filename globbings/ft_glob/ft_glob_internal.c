#include "ft_glob_internal.h"

void		*check_mem(t_glob_internal *gl, void *mem)
{
	if (!mem)
		gl->ret = FT_GLOB_NOSPACE;
	return (mem);
}

t_list		*ft_glob_internal(t_glob_internal *gl, const char *pattern,
				const char *path)
{
	enum e_pathtype	type;
	t_list		*match;
	const char	*cur_pattern;

	match = NULL;
	cur_pattern = NULL;
	type = slash_path(&pattern, &cur_pattern, gl);
	if (type == GL_END)
		match = add_slash(path, gl);
	else if (type == GL_RAWPATH)
		match = find_file(path, cur_pattern, *pattern != '/', gl);
	else if (type == GL_WILDCARD)
		match = match_files(path, cur_pattern, *pattern != '/', gl);
	ft_memdel((void **)&cur_pattern);
	if (!gl->ret && match && *pattern)
		return (match_next_pattern(gl, pattern, match));
	return (match);
}
