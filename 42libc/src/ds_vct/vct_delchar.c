#include "vctlib.h"

void	vct_delchar(t_vector *vct, size_t pos)
{
	if (vct != NULL && pos <= vct->len)
	{
		ft_memmove(vct->str + pos, vct->str + pos + 1, vct->len - pos);
		vct->len--;
	}
}
