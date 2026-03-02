#ifndef SCENE_H
# define SCENE_H

# include "map.h"

typedef struct s_player
{
	t_position	pos;
	double		angle;
}	t_player;

typedef struct s_camera
{
	double	fov;
	double	scale;
}	t_camera;

typedef struct s_scene
{
	char		**map;
	t_map_meta	map_meta;
	t_player	player;
	t_camera	camera;
}	t_scene;

#endif