#include "game.h"
#include "map.h"
#include "math_u.h"
#include "libft.h"

static int	rgb_to_int(t_rgb color);
static double	player_tile_to_angle(t_player_tile player_direction);
static bool copy_map(t_scene *scene, char **map);

bool game_init_scene(t_scene *scene, t_config *config, char **map, t_dimensions map_size)
{
    scene->map_size = map_size;
	scene->player.pos.x = 2.0;
	scene->player.pos.y = 2.0;
	scene->player.angle = player_tile_to_angle(TILE_PLAYER_EAST);
    scene->player.hit_radius = 0.4;
	scene->palette.ceiling = rgb_to_int(config->ceiling);
	scene->palette.floor = rgb_to_int(config->floor);
	// TODO: ERRO
	if (!copy_map(scene, map))
	{
		game_destroy_map(scene->map);
		scene->map = NULL;
		return (false);
	}	
	scene->camera.fov = deg_to_rad(FOV);
	scene->camera.scale = tan(scene->camera.fov / 2);
	return (true);
}

static int	rgb_to_int(t_rgb color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static double	player_tile_to_angle(t_player_tile player_direction)
{
	if (player_direction == TILE_PLAYER_NORTH)
		return (3 * M_PI / 2);
	if (player_direction == TILE_PLAYER_EAST)
		return (0.0);
	if (player_direction == TILE_PLAYER_WEST)
		return (M_PI);
	return (M_PI / 2);
}

static bool copy_map(t_scene *scene, char **map)
{
	int i;

	scene->map = ft_calloc(scene->map_size.height + 1, sizeof(char *));
	if (!scene->map)
		return (false);
	i = 0;
	while (i < scene->map_size.height)
	{
		scene->map[i] = ft_strdup(map[i]);
		if (!scene->map[i])
			return (false);
		i++;
	}
	scene->map[scene->map_size.height] = NULL;
	return (true);
}