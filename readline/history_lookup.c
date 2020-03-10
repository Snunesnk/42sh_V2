/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_lookup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:20:25 by snunes            #+#    #+#             */
/*   Updated: 2020/03/10 16:21:21 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void hist_lookup(void)
{
	char buf[10000];
	char *tmp;
	char *prompt;
	union u_buffer c;
	int i;

	tmp = g_line.line;
	i = 0;
	c.value = 1;
	ft_bzero(buf, 10000);
	prompt = ft_strdup(g_dis.prompt);
	set_prompt("(reverse-i-search)");
	while (ft_isprint(buf[i]) || !buf[i])
	{
		ft_putstr(tgoto(g_termcaps.ch, 0, 0));
		ft_putstr(g_dis.prompt);
		ft_putstr(tgoto(g_termcaps.clreol, 0, 0));
		ft_printf("`%s': %s", buf, tmp);
		c = read_key();
		if (c.value == 127 && i > 0)
			i--;
		if (test_c_value(c))
			break ;
		if (i >= 0)
			buf[i] = (c.value == 127) ? '\0' : c.value;
		if (c.value != 127)
			i++;
		if (c.value != 127 && !(get_matching_hist(&tmp, buf)))
			set_prompt("(failed reverse-i-search)");
		else if (ft_strequ(g_dis.prompt, "(failed reverse-i-search)"))
			set_prompt("(reverse-i-search)");
	}
	g_hist_lookup_value = c.value;
	set_prompt(prompt);
	free(prompt);
	if (i != 0 || tmp[0])
	{
		free(g_line.line);
		if (!(g_line.line = (char *)ft_memalloc(sizeof(char) * g_line.size_buf)))
			ft_printf("./21sh: cannot allocate memory\n");
		g_line.line = ft_memcpy(g_line.line, tmp, ft_strlen(tmp));
		g_line.len = ft_strlen(tmp);
		g_dis.cbpos = g_line.len;
	}
	update_line();
	return ;
}


