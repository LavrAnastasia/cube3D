#include "parsing.h"


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
		if (!is_valid_map_char(map[i]))
			return (0);
		i++;
	}
	return (1);
}


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
            if(map[y][x] == 'N' || map[y][x] == 'S' 
                || map[y][x] == 'E' || map[y][x] == 'W')
                count++;
            x++;
        }
        y++;
    }
    if(count != 1)
       return(0);
    return(1);
}

int is_player_start(char c)
{
    return(c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

double player_start_angle(char c)
{
    if(c == 'N')
        return(3.0 * M_PI / 2);
    if(c == 'S')
        return(M_PI / 2.0);
    if(c == 'W')
        return (M_PI);
    return (0.0);
}
int find_player_start(char **map, t_game *game)
{
    int x;
    int y;
    int count;
    char current_char;

    count = 0;
    y = 0;
    while(map[y])
    {
        x = 0;
        while(map[y][x] && map[y][x] != '\n')
        {
            current_char = map[y][x];
            if(is_player_start(current_char))
            {
                count++;
                game->scene.player.pos.x = x + 0.5;
                game->scene.player.pos.y = y + 0.5;
                game->scene.player.angle = player_start_angle(current_char);
                // map[y][x] = '0'; // чтобы в карте не оставался N/S/E/W (оставить ли?)
            }
            x++;
        }
        y++;
    }
    return(count == 1);
}

int is_walkable(char c)
{
    return(c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
    if(c == ' ')
        return 1;
    if(c == '1' || c == '*')
        return 0;
    if(!is_walkable(c))
        return 0;
    map[y][x] = '*';
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
int check_path(char **map, int rows, int player_x, int player_y)
{
    char **copy;
    int leak;

    copy = copy_map(map, rows);
    if(!copy)
        return(0);
    leak = flood_fill(copy, rows, player_x, player_y);
    free_map(copy, rows);
    return(leak == 0);
}

