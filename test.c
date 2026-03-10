#include "game.h"
#include "libft.h"
#include "render.h"
#include "movement.h"
// module engine
#include "math_u.h" // TODO: prbl delete in future
#include <mlx.h>

#include "keys.h" // TODO: place in GAME CONTROLS HANDLERS file

#define SIZE 10 // TODO: delete


// GAME LEVEL

// GAME LIVECYCEL
void game_shutdown(t_game *game)
{

	// TODO: DESTROY MAP and all memory objects
	textures_destroy(&game->textures, game->engine.mlx_session);
	engine_shutdown(&game->engine);
	exit(EXIT_SUCCESS);
}


// GAME CONTROLS HANDLERS
int game_on_key_down(int keycode, void *data)
{
	t_game *game;

	game = (t_game *)data;
	if (keycode == KEY_ESC)
		game->controls_state.quit_requested = true;
	else if (keycode == KEY_W)
		game->controls_state.move_forward = true;
	else if (keycode == KEY_S)
		game->controls_state.move_backward = true;
	else if (keycode == KEY_A)
		game->controls_state.move_left = true;
	else if (keycode == KEY_D)
		game->controls_state.move_right = true;
	else if (keycode == KEY_LEFT)
		game->controls_state.turn_left = true;
	else if (keycode == KEY_RIGHT)
		game->controls_state.turn_right = true;
	return (0);
}

int game_on_key_up(int keycode, void *data)
{
	t_game *game;

	game = (t_game *)data;
	if (keycode == KEY_W)
		game->controls_state.move_forward = false;
	else if (keycode == KEY_S)
		game->controls_state.move_backward = false;
	else if (keycode == KEY_A)
		game->controls_state.move_left = false;
	else if (keycode == KEY_D)
		game->controls_state.move_right = false;
	else if (keycode == KEY_LEFT)
		game->controls_state.turn_left = false;
	else if (keycode == KEY_RIGHT)
		game->controls_state.turn_right = false;
	return (0);
}

int game_on_close(void *data)
{
	t_game *game;

	game = (t_game *)data;
	game->controls_state.quit_requested = true;
	return (0);
}

int game_on_tick(void *data)
{
	t_game *game;

	game = (t_game *)data;
	if (game->controls_state.quit_requested)
	{
		game_shutdown(game);
		return (0);
	}

	update_player_movement(&game->scene, &game->controls_state);

	render_scene(&game->scene, game->engine.window_size, &game->engine.buffer.px, &game->textures);
	mlx_put_image_to_window(game->engine.mlx_session, game->engine.mlx_window,
						game->engine.buffer.img, 0, 0);
	return (0);
}
	
// GAME STARTs
int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	 static char *mock_map[SIZE] = {
		"1111111111",
		"1000000001",
		"1000000001",
		"1000010001",
		"1000010001",
		"1000010001",
		"1000010001",
		"1000000001",
		"1000000001",
		"1111111111"
	};

	// INIT_SCENE
	// Mock info
	game.scene.map_size.height = SIZE;
	game.scene.map_size.width = SIZE;

	game.scene.player.pos.x = 2.0;
	game.scene.player.pos.y = 2.0;

	game.scene.player.angle = 0.0;

	game.scene.palette.ceiling = 0x202030;
	game.scene.palette.floor = 0x151515;

	game.scene.map = ft_calloc(game.scene.map_size.height + 1, sizeof(char *));
	if (!game.scene.map)
		return (1); // TODO: error handling
	int i = 0;
	for (i = 0; i < game.scene.map_size.height; i++) {
		game.scene.map[i] = ft_strdup(mock_map[i]);
		if (!game.scene.map[i])
			return (1); // TODO: error handling + cleanup
	}   

	game.scene.map[game.scene.map_size.height] = NULL;

	game.scene.camera.fov = deg_to_rad(FOV);
	game.scene.camera.scale = tan(game.scene.camera.fov / 2);

	// INIT ENGINE
	game.engine.window_size = (t_dimensions){
		.width = MAX_WIN_WIDTH,
		.height = MAX_WIN_HEIGHT
	};

	if (engine_init(&game.engine, GAME_TITLE) != ENGINE_OK) {
		// TODO: clean other sources
		return (1);
	}

	game.engine.events.data = &game;
	game.engine.events.on_close = game_on_close;
	game.engine.events.on_key_down = game_on_key_down;
	game.engine.events.on_key_up = game_on_key_up;
	game.engine.events.on_tick = game_on_tick;

	// LOAD TEXTURES
	const t_wall_texture_paths paths = (t_wall_texture_paths) {
		.east =  "resources/ea.xpm",
		.north = "resources/no.xpm",
		.south = "resources/so.xpm", 
		.west = "resources/we.xpm"
	};

	if (textures_load(&game.textures, game.engine.mlx_session, &paths) != TEX_OK) {
		engine_shutdown(&game.engine);
		return (1);
	}
	engine_run(&game.engine);

	return (0);
}