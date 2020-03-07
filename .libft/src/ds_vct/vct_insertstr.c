#include "vctlib.h"

static int	insert(const char *str, const size_t pos, t_vector *vct)
{
	size_t	len;
	int		ret;

	ret = SUCCESS;
	len = ft_strlen(str);
	vct->len += len;
	if (vct->len + 1 > vct->size)
		ret = vct_resize(vct);
	if (ret == SUCCESS)
	{
		ft_memmove(vct->str + pos + len, vct->str + pos, vct->len - len);
		ft_memcpy(vct->str + pos, str, len);
	}
	return (ret);
}

int			vct_insertstr(const char *str, const size_t pos, t_vector *vct)
{
	int		ret;

	ret = SUCCESS;
	if (vct == NULL)
		ret = FAILURE;
	else
		ret = insert(str, pos, vct);
	return (ret);
}
