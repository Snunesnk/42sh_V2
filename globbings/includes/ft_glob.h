#ifndef FT_GLOB_H
# define FT_GLOB_H

# include <stddef.h>

typedef struct	s_glob
{
	size_t	gl_pathc;	/* Count of matched paths so far */
	char	**gl_pathv;	/* List of matched path names */
	size_t	gl_offs;	/* Slots to reserve in gl_pathv */
}		t_glob;

/*
** Glob flags
*/

# define	FT_GLOB_ERR		0x001	/* Return on read errors */
# define	FT_GLOB_MARK		0x002	/* Append slash to directories */
# define	FT_GLOB_NOSORT		0x004	/* Do not sort the result */
# define	FT_GLOB_DOOFFS		0x008	/* Reserve slots in gl_pathv */
# define	FT_GLOB_NOCHECK		0x010	/* Return the pattern if no match */
# define	FT_GLOB_APPEND		0x020	/* Append the result to preceding call */
# define	FT_GLOB_NOESCAPE	0x040	/* A '\' is a regular character */
# define	FT_GLOB_PERIOD		0x080	/* Allow leading period to be matched */
# define	FT_GLOB_BRACE		0x100	/* Expand brace expressions */

/* TODO: not implemented yet */
# define	FT_GLOB_TILDE		0x200	/* Expand tildes */
# define	FT_GLOB_TILDE_CHECK	0x400	/* Expand tildes but NOMATCH on fail */

/*
** Glob return values
*/

# define	FT_GLOB_NOSPACE		0x001
# define	FT_GLOB_ABORTED		0x002
# define	FT_GLOB_NOMATCH		0x004

int		ft_glob(const char *pattern, int flags,
			int (*errfunc)(const char *epath, int eerrno),
			t_glob *pglob);

void		ft_globfree(t_glob *pglob);

#endif
