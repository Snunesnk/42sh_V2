# include "ft_readline.h"

_Bool	g_ctrl_mode = 0;

static void	switch_cbpos(void)
{
	insert_text("Hello", 5);
	return ;
}

void	rl_ctrl_mode(union u_buffer u)
{
	if (g_ctrl_mode)
	{
		if (u.buf[0] == 24 && u.buf[1] == 0)
			switch_cbpos();
	}
	g_ctrl_mode ^= 1;
}
