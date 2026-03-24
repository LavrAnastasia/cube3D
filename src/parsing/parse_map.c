#include "parsing_internal.h"

int row_len(char *s)
{
    int i = 0;
    while(s[i] && s[i] != '\n')
        i++;
    return(i);
}

t_dimensions calc_map_size(char **map)
{	
	t_dimensions size;

	size.width = 0;
	size.height = 0;
	int max_width;

	if(!map)
		return size;
	while (map[size.height])
	{
		max_width = row_len(map[size.height]);
        if(max_width > size.width)
            size.width = max_width;
		size.height++;
	}
	return (size);
}

t_parse_result	validate_map(char **map, t_configuration *configuration, int height)
{
	if (!is_valid_map_rows(map))
		return make_parse_error_result(P_ERR_INVALID_SYMBOLS, NULL);
    if (!validate_payer_pos(map, configuration))
		return make_parse_error_result(P_ERR_PLAYER_COUNT, NULL);
	return (is_map_closed(map, height, configuration->player_pos));
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

bool is_empty_map_line(char *line)
{
	char *str;

	str = skip_spaces(line);
	if(!str || *str == '\0' || *str == '\n')
		return (true);
	return (false);
}

t_parse_result	read_map(int fd, char **map_in_one_line)
{
	char	*line;
	char	*tmp;

	if (fd < 0 || !map_in_one_line)
		return (make_parse_error_result(P_ERR_EMPTY_MAP, NULL));
	line = get_next_line(fd);
	while (line)
	{
		if(is_empty_map_line(line))
		{
			free(line);
			return(make_parse_error_result(P_ERR_MAP_EMPTY_LINE, NULL));
		}
		if(!is_map_row(line))
		{
			free(line);
			return(make_parse_error_result(P_ERR_INVALID_SYMBOLS, NULL));
		}
		tmp = join_lines(*map_in_one_line, line);
		if (!tmp)
		{
			*map_in_one_line = NULL;
			return (make_parse_error_result(P_ERR_MALLOC, NULL));
		}
		*map_in_one_line = tmp;
		line = get_next_line(fd);
	}
	return (make_parse_success_result(P_MAP));
}

t_parse_result	parse_map(int fd, t_configuration *configuration, char *first_map_line)
{
	char			**map;
	char			*map_in_one_line;
	t_parse_result	result;
	t_dimensions map_size;

	if (!first_map_line)
		return (make_parse_error_result(P_ERR_EMPTY_MAP, NULL));
	map_in_one_line = ft_strdup(first_map_line);
	if (!map_in_one_line)
		return (make_parse_error_result(P_ERR_MALLOC, NULL));
	result = read_map(fd, &map_in_one_line);
	if (!result.ok)
	{
		if(map_in_one_line)
			free(map_in_one_line);
		return (result);
	}
	map = ft_split(map_in_one_line, '\n');
	free(map_in_one_line);
	if (!map || !map[0])
	{
		free_str_array(map);
		return (make_parse_error_result(P_ERR_EMPTY_MAP, NULL));
	}
	map_size = calc_map_size(map);

	result = validate_map(map, configuration, map_size.height);
	if (!result.ok)
	{
		free_str_array(map);
		return (result);
	}
    configuration->map = map;
	configuration->map_size = map_size;
	return (make_parse_success_result(P_MAP));
}
