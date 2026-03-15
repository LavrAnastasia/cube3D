#ifndef CONFIG_H
#define CONFIG_H

#include "colors.h"
#include "textures_types.h"

typedef struct s_config
{
    t_wall_texture_paths paths;
    t_rgb floor;
    t_rgb ceiling;
}t_config;

#endif 