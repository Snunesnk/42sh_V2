#include "vctlib.h"

void	vct_dellastchar(t_vector *vct)
{
	if (vct != NULL)
	{
		vct->len--;
		vct->str[vct->len] = '\0';
	}
}
