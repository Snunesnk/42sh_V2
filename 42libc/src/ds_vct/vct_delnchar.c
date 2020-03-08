#include "vctlib.h"

void	vct_delnchar(t_vector *vct, size_t pos, size_t n)
{
	if (vct != NULL && pos <= vct->len)
	{
		ft_memmove(vct->str + pos, vct->str + pos + n, vct->len - pos - n);
		vct->len -= n;
	}
}
