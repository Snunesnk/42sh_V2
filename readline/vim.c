#include "ft_readline.h"
#include "../src/builtins/builtins.h"

void	vim_hash(void)
{
	g_input_break = 1;
	g_dis.cbpos = 0;
	insert_text("#", 1);
}

void	call_fc(void)
{ /* Need some help from Simon to better implement this */
	char *argv[2];

	argv[0] = "fc";
	argv[1] = NULL;
	cmd_fc(1, argv);
}
