#include "parsing.h"
#include "map_utils.h"


bool	is_valid_map_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW \n", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map_chars(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (!is_valid_map_char(map[i])) // TODO: how to use is_valid_char && SKIP_SIGN && \n loook down
			return (0);
		i++;
	}
	return (1);
}

// int	is_valid_map_chars(char **map)
// {
// 	int	i;
// 	int	j;
// 	char	c;

// 	if (!map || !map[0])
// 		return (0);
// 	i = 0;
// 	while (map[i])
// 	{
// 		j = 0;
// 		while (map[i][j])
// 		{
// 			c = map[i][j];
// 			if (!is_valid_char(c) && c != SKIP_SIGN && c != '\n')
// 				return (0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (1);
// }



bool is_one_player(char **map)
{
    int x;
    int y;
    int count;

    count = 0;
    y = 0;
    while(map[y])
    {
        x = 0;
        while(map[y][x] && map[y][x] != '\n')
        {
            if(is_player_pos(map[y][x]))
            {
                if (count > 0)
                    return (false);
                count++;
            }
               
            x++;
        }
        y++;
    }
    return (count == 1);
}



void find_player_start(char **map, t_configuration *configuration)
{
    int x;
    int y;
    char current_char;

    y = 0;
    while(map[y])
    {
        x = 0;
        while(map[y][x] && map[y][x] != '\n')
        {
            current_char = map[y][x];
            if(is_player_pos(current_char))
            {
                configuration->player_pos.x = x + 0.5;
                configuration->player_pos.y = y + 0.5;
                configuration->player_start = current_char;
            }
            x++;
        }
        y++;
    }
}

int is_walkable(char c)
{
    return(c == TILE_EMPTY || is_player_pos(c));
}
int flood_fill(char **map, int rows, int x, int y)
{
    int len;
    char c;

    if(y < 0 || y >= rows || x < 0)
        return 1;
    len = row_len(map[y]);
    if(x >= len)
        return 1;
    c = map[y][x];

    if(c == SKIP_SIGN)
        return 1;
    if(c == TILE_WALL || c == VISITED_SIGN)
        return 0;
    if(!is_walkable(c))
        return 0;
    map[y][x] = VISITED_SIGN;
    if (flood_fill(map, rows, x - 1, y))
		return (1);
	if (flood_fill(map, rows, x + 1, y))
		return (1);
	if (flood_fill(map, rows, x, y - 1))
		return (1);
	if (flood_fill(map, rows, x, y + 1))
		return (1);
    return 0;
}

char **copy_map(char **map, int rows)
{
    char **copy;
    int i;

    copy = malloc(sizeof(char *)*(rows + 1));
    if(!copy)
        return NULL;
    i = 0;
    while(i < rows)
    {
        copy[i] = ft_strdup(map[i]);
        if(!copy[i])
            return(free_map(copy, i), NULL);
        i++;
    }
    copy[i] = NULL;
    return(copy);
}

void free_map(char **map, int rows)
{
    int i;

    if(!map)
        return;
    i = 0;
    while(i < rows)
    {
        free(map[i]);
        i++;
    }
    free(map);
}
int check_path(char **map, int rows, t_position position)
{
    char **copy;
    int leak;

    copy = copy_map(map, rows);
    if(!copy)
        return(0);
    leak = flood_fill(copy, rows, position.x, position.y);
    free_map(copy, rows);
    return(leak == 0);
}

