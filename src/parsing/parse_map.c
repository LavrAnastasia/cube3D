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

int	map_height(char **map)
{
	int	row;

	row = 0;
	while (map && map[row])
		row++;
	return (row);
}

int	map_width(char **map)
{
    int row = 0;
    int col = 0;
    int len;

    while(map && map[row])
    {
        len = row_len(map[row]);
        if(len > col)
            col = len;
        row++;
    }
    return(col);
}

t_parse_result	validate_map(char **map, t_game *game)
{
    int height;

    height = map_height(map);
	if (!is_valid_map_chars(map))
		return make_parse_error_result(P_ERR_INVALID_SYMBOLS);
    if(!is_one_player(map))
        return make_parse_error_result(P_ERR_PLAYER_COUNT);
    if (!find_player_start(map, game))
	    return (make_parse_error_result(P_ERR_PLAYER_COUNT));
	if (!check_path(map, height, (int)game->scene.player.pos.x,
    (int)game->scene.player.pos.y))
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
		if (s[i] == ' ')
			s[i] = '0';
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

t_parse_result	parse_map(int fd, t_game *game, char *first_map_line)
{
	char			**map;
	char			*map_in_one_line;
	t_parse_result	result;

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
	result = validate_map(map, game);
	if (!result.ok)
	{
		free_split(map);
		return (result);
	}
    game->scene.map = map;
	game->scene.map_size.height = map_height(map);
	game->scene.map_size.width = map_width(map);
	return (make_parse_success_result(P_MAP));
}
