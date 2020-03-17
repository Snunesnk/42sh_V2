
int	ft_fnm_is_print(char c)
{
	return ((c >= ' ' && c <= '~'));
}

int	ft_fnm_is_xdigit(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'));
}
