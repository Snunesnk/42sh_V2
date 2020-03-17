#include "ft_readline.h"

/* Insert mode */
struct s_keymap_entry g_vim_standard_insert_keymap[] =
{
	[ 0 ... 22 ] = { ISFUNC, rl_void },
	{ ISFUNC, cut_prev_wd },
	[ 24 ... 26 ] = { ISFUNC, rl_void },
	{ ISKMAP, vim_escape }, /* Escape */
	[ 28 ... 31 ] = { ISFUNC, rl_void },
	[ ' ' ... '~' ] = { ISFUNC, rl_insert },
	{ ISFUNC, rl_backspace }	
};

struct s_keymap_entry g_vim_ctlx_insert_keymap[] =
{
	[ 0 ... 50 ] = { ISFUNC, rl_void },
	{ ISFUNC, rl_delete },
	[ 52 ... 64 ] = { ISFUNC, rl_void },
	{ ISFUNC, history_up },
	{ ISFUNC, history_down },
	{ ISFUNC, cursor_r },
	{ ISFUNC, cursor_l },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_end },
	{ ISFUNC, rl_void },
	{ ISFUNC, rl_home },
	[ 73 ... 84 ] = { ISFUNC, rl_void },
	{ ISFUNC, cursor_u },
	{ ISFUNC, cursor_d },
	{ ISFUNC, wd_right },
	{ ISFUNC, wd_left },
	[ 89 ... 127 ] = { ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_meta_insert_keymap[] =
{
	[ 0 ... 127 ] = { ISFUNC, rl_void }
};

/* Command mode */
struct s_keymap_entry g_vim_standard_cmd_keymap[] =
{
	[ 0 ... 31 ] = { ISFUNC, rl_void },
	{ ISFUNC, cursor_r },
	[ 33 ... 34 ] = { ISFUNC, rl_void },
	{ ISFUNC, vim_hash },
	[ 36 ... 103 ] = { ISFUNC, rl_void },
	{ ISFUNC, cursor_l },
	{ ISFUNC, vim_insert },
	{ ISFUNC, history_down },
	{ ISFUNC, history_up },
	{ ISFUNC, cursor_r },
	[ 109 ... 117 ] = { ISFUNC, rl_void },
	{ ISFUNC, call_fc },
	[ 119 ... 127 ] = { ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_ctlx_cmd_keymap[] =
{
	[ 0 ... 127 ] = { ISFUNC, rl_void }
};

struct s_keymap_entry g_vim_meta_cmd_keymap[] =
{
	[ 0 ... 127 ] = { ISFUNC, rl_void }
};
