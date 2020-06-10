#include "interactive_test.h"

int		is_str_digit(char *str)
{
	int	i = 0;

	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_isprint(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

int		ft_strequ(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == s2[i])
		return (1);
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		len;

	if (!s1)
		return (strdup(s2));
	len = strlen(s1) + strlen(s2) + 1;
	if (!(joined = (char *)malloc(sizeof(char) * len)))
	{
		perror("malloc");
		exit(1);
	}
	bzero(joined, len);
	joined = strcat(joined, s1);
	joined = strcat(joined, s2);
	return (joined);
}

char	*get_filename(char *path)
{
	int	i;

	i = strlen(path);
	while (i > 0 && path[i] != '/')
		i--;
	return (path + i + 1);
}
