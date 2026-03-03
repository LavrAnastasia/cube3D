#include "parsing.h"

void init_config(t_config *config)
{
    config->no_path = NULL;
    config->so_path = NULL;
    config->we_path = NULL;
    config->ea_path = NULL;
    config->floor.r = -1;
    config->floor.g = -1;
    config->floor.b = -1;
    config->ceiling.r = -1;
    config->ceiling.g = -1;
    config->ceiling.b = -1;
}