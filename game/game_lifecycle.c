#include <stdlib.h>

#include "game.h"

void game_shutdown(t_game *game, int exit_status)
{

	// TODO: DESTROY MAP and all memory objects
	textures_destroy(&game->textures, game->engine.mlx_session);
	engine_shutdown(&game->engine);
	exit(exit_status);
}