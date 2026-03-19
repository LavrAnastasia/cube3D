/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:03 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/19 15:38:06 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "libft.h"
#include "map.h"
#include "math_u.h"
#include "reporter.h"
#include "scene_status.h"

static int		rgb_to_int(t_rgb color);
static double	player_tile_to_angle(t_player_tile player_direction);
static bool		copy_map(t_scene *scene, char **map);

bool	game_init_scene(t_scene *scene, t_configuration *configuration)
{
	scene->map_size = configuration->map_size;
	scene->player.pos = configuration->player_pos;
	scene->player.angle = player_tile_to_angle(configuration->player_start);
	scene->player.hit_radius = 0.4;
	scene->palette.ceiling = rgb_to_int(configuration->samples.ceiling);
	scene->palette.floor = rgb_to_int(configuration->samples.floor);
	if (!copy_map(scene, configuration->map))
	{
		report(D_SCENE, SC_ERR_MALLOC, SL_ERROR);
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

static bool	copy_map(t_scene *scene, char **map)
{
	int	i;

	scene->map = ft_calloc(scene->map_size.height + 1, sizeof(char *));
	if (!scene->map)
		return (false);
	i = 0;
	while (i < scene->map_size.height)
	{
		scene->map[i] = ft_strdup(map[i]);
		if (!scene->map[i])
		{
			game_destroy_map(scene->map);
			scene->map = NULL;
			return (false);
		}
		i++;
	}
	scene->map[scene->map_size.height] = NULL;
	return (true);
}
