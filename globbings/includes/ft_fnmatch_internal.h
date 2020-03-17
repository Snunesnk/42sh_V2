#ifndef FT_FNMATCH_INTERNAL_H
# define FT_FNMATCH_INTERNAL_H

# define FT_FNM_EXTMASK		0x0f	/* Get the external flags only */

# define FT_IFNM_SKIP		0x10	/* Skip the current char (useful for '\') */
# define FT_IFNM_FORCE_REG	0x20	/* The current character is not sepecial */
# define FT_IFNM_LEADING_PERIOD	0x40	/* The current '.' if any, is leading */

# define CASE_OFFSET		32	/* For case insensitive matching */

# define BRACK_SPEC_CHARS	"\\!:-]"
# define GLOB_SPEC_CHARS	"\\?[*"


typedef struct	s_flags
{
	int	cur;
	int	next;
}		t_flags;

int	set_flags(char pattern, char string, t_flags *flags);
int	match_star(const char **pattern, const char **string, t_flags *flags);
int	explicit_match(char string, t_flags *flags);
int	match_qmark(const char **pattern, const char **string, t_flags *flags);
int	match_reg(const char **pattern, const char **string);
int	match_brack(const char **pattern, const char **string, t_flags *flags);
int	ft_fnmatch_internal(const char *pattern, const char *string,
		t_flags flags);

#endif
