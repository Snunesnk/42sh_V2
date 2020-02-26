#include "vctlib.h"

static int	insert(const char c, const size_t pos, t_vector *vct)
{
	int		ret;

	ret = SUCCESS;
	if (vct->len + 1 > vct->size)
		ret = vct_resize(vct);
	if (ret == SUCCESS)
	{
		ft_memmove(vct->str + pos + 1, vct->str + pos, vct->len - pos);
		vct->str[pos] = c;
		vct->len++;
	}
	return (ret);
}

int			vct_insertchar(const char c, const size_t pos, t_vector *vct)
{
	int		ret;

	ret = SUCCESS;
	if (vct == NULL)
		ret = FAILURE;
	else
		ret = insert(c, pos, vct);
	return (ret);
}
