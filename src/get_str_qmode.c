#include <unistd.h>
#include "libft.h"
#include "quotes.h"

int		double_quote_print_fd(const char *str, int fd)
{
	int		ret;
	char	*next;

	ret = write(fd, "\"", 1);
	while (*str)
	{
		if (*str == '\\' || *str == '"')
			ret += ft_dprintf(fd, "\\%c", *str++);
		else
		{
			if (!(next = ft_strchr(str, '\\'))
				&& !(next = ft_strchr(str, '"')))
				next = ft_strchr(str, 0);
			ret += write(fd, str, next - str);
			str = next;
		}
	}
	ret += write(fd, "\"", 1);
	return (ret);
}

int		single_quote_print_fd(const char *str, int fd)
{
	int		ret;
	char	*next;

	if (!ft_strchr(str, '\''))
		return (ft_dprintf(fd, "'%s'", str));
	ret = write(fd, "'", 1);
	while (*str)
	{
		if (*str == '\'')
		{
			ret += write(fd, "'\\''", 4);
			++str;
		}
		else
		{
			if (!(next = ft_strchr(str, '\'')))
				next = ft_strchr(str, 0);
			ret += write(fd, str, next - str);
			str = next;
		}
	}
	ret += write(fd, "'", 1);
	return (ret);
}

int		get_str_qmode_set(int qmode, char *s, int quote_set)
{
	while (*s)
		qmode = get_qmode(qmode, *s++) & quote_set;
	return (qmode);
}

int		get_str_qmode(int qmode, char *s)
{
	while (*s)
		qmode = get_qmode(qmode, *s++);
	return (qmode);
}
