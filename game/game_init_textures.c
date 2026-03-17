#include "game.h"

bool game_init_textures(t_textures *textures, t_config *config, void *mlx_session)
{
    const t_wall_texture_paths paths = (t_wall_texture_paths) {
		.east =  config->ea_path,
        .north = config->no_path,
        .south = config->so_path, 
        .west = config->we_path
	};

	if (textures_load(textures, mlx_session, &paths) != TEX_OK)
		return (false);
    return (true);
}