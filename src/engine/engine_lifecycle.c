#include <stdlib.h> // TODO: delete, uses for exit func

#include "engine.h"

// TODO: think about it 
// Previously, the game had a single exit function.
// Should quitting be handled by the engine, or by the game/app layer?


// Private API

#ifdef __linux__

void	clean_mlx_session(t_game *game)
{
	mlx_destroy_display(game->mlx_session);
	free(game->mlx_session);
}
#else

void	clean_mlx_session(t_game *game)
{
	(void)(game);
}
#endif

static void	*load_xpm(t_game *game, const char *path)
{
	int	size;

	size = TILE_SIZE;
	return (
		mlx_xpm_file_to_image(
			game->mlx_session,
			(char *)path,
			&size,
			&size
		)
	);
}

static void	load_sprites(t_game *game)
{
    // TODO: read form real config
    const char *NO =  "resources/no.xpm";
    const char *SO =  "resources/so.xpm";
    const char *EA =  "resources/ea.xpm";
    const char *WE =  "resources/we.xpm";

    game->map_meta.sprites.north_texture = load_xpm(game, NO);
    game->map_meta.sprites.south_texture = load_xpm(game, SO);
	game->map_meta.sprites.east_texture = load_xpm(game, EA);
	game->map_meta.sprites.west_texture = load_xpm(game, WE);
    if (!game->map_meta.sprites.north_texture
        || !game->map_meta.sprites.south_texture
		|| !game->map_meta.sprites.east_texture
		|| !game->map_meta.sprites.west_texture)
	{
        engine_shutdown(game);
        exit(1); // TODO: return control flow to app
    }
}

static void	init_mlx(t_game *game)
{
	game->mlx_session = mlx_init();
	if (!game->mlx_session)
	{
        engine_shutdown(game);
        exit(1); // TODO: return control flow to app
    }
	game->mlx_window = mlx_new_window(
			game->mlx_session,
			game->map_meta.width * TILE_SIZE,
			game->map_meta.height * TILE_SIZE,
			GAME_TITLE);
	if (!game->mlx_window)
	{
        engine_shutdown(game);
        exit(1);  // TODO: return control flow to app
    }
}

static void	destroy_textures(t_game *game)
{
	if (game->map_meta.sprites.north_texture)
		mlx_destroy_image(game->mlx_session, game->map_meta.sprites.north_texture);
	if (game->map_meta.sprites.south_texture)
		mlx_destroy_image(game->mlx_session, game->map_meta.sprites.south_texture);
	if (game->map_meta.sprites.east_texture)
		mlx_destroy_image(game->mlx_session, game->map_meta.sprites.east_texture);
	if (game->map_meta.sprites.west_texture)
		mlx_destroy_image(game->mlx_session, game->map_meta.sprites.west_texture);
}

// Public API

void	engine_init(t_game *game)
{
    init_mlx(game);  // TODO: should check and return control flow to app
    load_sprites(game); // TODO: should check and return control flow to app
}

void engine_shutdown(t_game *game)
{
    destroy_textures(game);
    if (game->mlx_session && game->mlx_window)
		mlx_destroy_window(game->mlx_session, game->mlx_window);
	if (game->mlx_session)
		clean_mlx_session(game);
}