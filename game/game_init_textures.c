#include "game.h"
#include "parsing.h"

bool game_init_textures(t_textures *textures, t_configuration *configuration, void *mlx_session)
{
	if (textures_load(textures, mlx_session, &configuration->samples.paths) != TEX_OK)
		return (false);
  return (true);
}