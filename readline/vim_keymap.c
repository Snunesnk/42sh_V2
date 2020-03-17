#include "ft_readline.h"

struct s_keymap_entry g_vim_standard_keymap[] =
{
	[ 0 ... 26 ] = { ISFUNC, rl_void },
	{ ISKMAP, vim_escape }, /* Escape */
	[ 28 ... 31 ] = { ISFUNC, rl_void },
	[ ' ' ... '~' ] = { ISFUNC, rl_insert },
	{ ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_ctlx_keymap[] =
{
	[ 0 ... 104 ] = { ISFUNC, rl_void },
	{ ISFUNC, vim_insert },
	[ 106 ... 127 ] = { ISFUNC, rl_void },
};

struct s_keymap_entry g_vim_meta_keymap[] =
{
	[ 0 ... 127 ] = { ISFUNC, rl_void },
};
