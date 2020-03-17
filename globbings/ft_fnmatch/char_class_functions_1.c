int	ft_fnm_is_alnum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

int	ft_fnm_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_fnm_is_punct(char c)
{
	return ((c >= '!' && c <= '/') || (c >= ':' && c <= '@')
		|| (c >= '[' && c <= '`') || (c >= '{' && c <= '~'));
}

int	ft_fnm_is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_fnm_is_graph(char c)
{
	return (c >= '!' && c <= '~');
}
