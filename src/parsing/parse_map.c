#include "parsing.h"

static t_parse_result	make_parse_error_result(t_parse_error_code code)
{
	return ((t_parse_result){.ok = false, .error = (t_parse_error){.code = code,
		.info = NULL}});
}

static t_parse_result	make_parse_success_result(t_parse_type p_type)
{
	return ((t_parse_result){.ok = true, .parse_type = p_type});
}
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
	if (!is_valid_map_chars(map))
		return make_parse_error_result(P_ERR_INVALID_SYMBOLS);
    if(!is_one_player(map))
        return make_parse_error_result(P_ERR_PLAYER_COUNT);
    if (!find_player_start(map, configuration))
	    return (make_parse_error_result(P_ERR_PLAYER_COUNT));
	if (!check_path(map, height, (int)configuration->player_pos.x,
    (int)configuration->player_pos.y))
	        return (make_parse_error_result(P_ERR_MAP_NOT_CLOSED)); //добавить сообщение об ошибке
	    return (make_parse_success_result(P_MAP));
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

static void	replace_spaces(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == SKIP_SIGN)
			s[i] = TILE_EMPTY;
		i++;
	}
}

t_parse_result	read_map(int fd, char **map_in_one_line)
{
	char	*line;
	char	*tmp;

	if (fd < 0 || !map_in_one_line)
		return (make_parse_error_result(P_ERR_NO_MAP)); // UPDATE ERROR
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = join_lines(*map_in_one_line, line);
		if (!tmp)
			return (make_parse_error_result(P_ERR_MALLOC));
		*map_in_one_line = tmp;
	}
    replace_spaces(*map_in_one_line);
	return (make_parse_success_result(P_MAP));
}

t_parse_result	parse_map(int fd, t_configuration *configuration, char *first_map_line)
{
	char			**map;
	char			*map_in_one_line;
	t_parse_result	result;
	t_dimensions map_size;

	if (!first_map_line)
		return (make_parse_error_result(P_ERR_NO_MAP));
	map_in_one_line = ft_strdup(first_map_line);
	if (!map_in_one_line)
		return (make_parse_error_result(P_ERR_MALLOC));
	result = read_map(fd, &map_in_one_line);
	if (!result.ok)
	{
		free(map_in_one_line);
		return (result);
	}
	map = ft_split(map_in_one_line, '\n');
	free(map_in_one_line);
	if (!map || !map[0])
	{
		free_split(map);
		return (make_parse_error_result(P_ERR_NO_MAP)); // UPDATE ERROR
	}
	map_size = calc_map_size(map);
	result = validate_map(map, configuration, map_size.height);
	if (!result.ok)
	{
		free_split(map);
		return (result);
	}
    configuration->map = map;
	configuration->map_size = map_size;
	return (make_parse_success_result(P_MAP));
}
