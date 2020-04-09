#include "ft_readline.h"

void	insert_compl(t_node *compl_tree, t_data *data)
{
	char	*compl;
	size_t	len;

	while (compl_tree && data->chosen_exec != compl_tree->nb_node)
	{
		if (data->chosen_exec > compl_tree->nb_node)
			compl_tree = compl_tree->right;
		else
			compl_tree = compl_tree->left;
	}
	compl = compl_tree->name;
	len = ft_strlen(compl);
	while (g_dis.cbpos > data->compl_start)
		rl_backspace();
	insert_text(compl, len);
}
