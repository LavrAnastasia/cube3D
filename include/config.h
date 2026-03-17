#ifndef CONFIG_H
#define CONFIG_H

#include "colors.h"
#include "map.h"
#include "textures_types.h"

typedef struct s_config
{
    t_wall_texture_paths paths;
    t_rgb floor;
    t_rgb ceiling;
}t_config;

typedef struct s_configuration {
	char			**map;
	t_dimensions	map_size;
	t_position		player_pos;
	t_player_tile	player_start;
	t_config		samples;
} t_configuration;
#endif 