#include "parsing.h"
#include "map_utils.h"

int	is_valid_map_rows(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		if (!is_map_row(map[i]))
			return (0);
		i++;
	}
	return (1);
}


bool validate_payer_pos(char **map, t_configuration *config)
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
                config->player_pos.x = x + 0.5;
                config->player_pos.y = y + 0.5;
                config->player_start = map[y][x];
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

    copy = ft_calloc(rows + 1, sizeof(char *));
    if(!copy)
        return NULL;
    i = 0;
    while(i < rows)
    {
        copy[i] = ft_strdup(map[i]);
        if(!copy[i])
            return(free_str_array(copy), NULL);
        i++;
    }
    copy[i] = NULL;
    return(copy);
}
int is_map_closed(char **map, int rows, t_position position)
{
    char **copy;
    int leak;

    copy = copy_map(map, rows);
    if(!copy)
        return(0);
    leak = flood_fill(copy, rows, position.x, position.y);
    free_str_array(copy);
    return(leak == 0);
}

