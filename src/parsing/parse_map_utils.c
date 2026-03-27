#include "parsing_internal.h"

int	row_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

t_dimensions	calc_map_size(char **map)
{
	t_dimensions	size;
	int				max_width;

	size.width = 0;
	size.height = 0;
	if (!map)
		return (size);
	while (map[size.height])
	{
		max_width = row_len(map[size.height]);
		if (max_width > size.width)
			size.width = max_width;
		size.height++;
	}
	return (size);
}

char	*join_lines(char *s1, char *s2)
{
	char	*joined_line;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		joined_line = ft_strdup(s2);
	else if (!s2)
		joined_line = ft_strdup(s1);
	else
		joined_line = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined_line);
}

bool	is_empty_map_line(char *line)
{
	char	*str;

	str = skip_spaces(line);
	if (!str || *str == '\0' || *str == '\n')
		return (true);
	return (false);
}