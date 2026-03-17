#include <stdlib.h>

#include "game.h"

void game_shutdown(t_game *game, int exit_status)
{
	game_destroy_map(game->scene.map);
	game->scene.map = NULL;
	textures_destroy(&game->textures, game->engine.mlx_session);
	engine_shutdown(&game->engine);
	exit(exit_status);
}

void game_destroy_map(char **map)
{
	size_t	i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}