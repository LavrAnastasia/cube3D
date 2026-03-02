#ifndef CONFIG_H
#define CONFIG_H

#include "colors.h"

typedef struct s_config
{
    char *no_path;
    char *so_path;
    char *we_path;
    char *ea_path;

    t_rgb floor;
    t_rgb ceiling;
}t_config;

#endif 