/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:01:05 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 23:05:46 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "types.h"

typedef struct s_player
{
	t_position	pos;
	double		angle;
	double		hit_radius;
}	t_player;

typedef struct s_camera
{
	double	fov;
	double	scale;
}	t_camera;

typedef struct s_palette
{
	t_color	ceiling;
	t_color	floor;
}	t_palette;

typedef struct s_scene
{
	char			**map;
	t_dimensions	map_size;
	t_player		player;
	t_camera		camera;
	t_palette		palette;
	double			last_update_time_seconds;
}	t_scene;

#endif