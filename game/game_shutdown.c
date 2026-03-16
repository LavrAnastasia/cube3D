#include <stdlib.h>

#include "game.h"

void game_shutdown(t_game *game, int exit_status)
{

	size_t  i;

	if (game->scene.map)
	{
		i = 0;
		while (game->scene.map[i])
		{
			free(game->scene.map[i]);
			i++;
		}
		free(game->scene.map);
	}
	textures_destroy(&game->textures, game->engine.mlx_session);
	engine_shutdown(&game->engine);
	exit(exit_status);
}