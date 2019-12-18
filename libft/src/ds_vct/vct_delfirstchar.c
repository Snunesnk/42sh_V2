#include "vctlib.h"

void	vct_delfirstchar(t_vector *vct)
{
	if (vct != NULL)
	{
		ft_memmove(vct->str, vct->str + 1, vct->len);
		vct->len--;
	}
}
