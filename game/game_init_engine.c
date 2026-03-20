/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:50:59 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:44:24 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "mlx.h"
#include "game_internal.h"
#include "game_settings.h"
#include "keys.h"
#include "movement.h"
#include "render.h"

static int	game_on_key_down(int keycode, void *data);
static int	game_on_key_up(int keycode, void *data);
static int	game_on_close(void *data);
static int	game_on_tick(void *data);

bool	game_init_engine(t_game *game)
{
	t_engine_status	status;

	game->engine.window_size = (t_dimensions){.width = MAX_WIN_WIDTH,
		.height = MAX_WIN_HEIGHT};
	status = engine_init(&game->engine, GAME_TITLE);
	if (status != ENGINE_OK)
	{
		report(D_ENGINE, status, SL_ERROR);
		return (false);
	}
	game->engine.events.data = game;
	game->engine.events.on_close = game_on_close;
	game->engine.events.on_key_down = game_on_key_down;
	game->engine.events.on_key_up = game_on_key_up;
	game->engine.events.on_tick = game_on_tick;
	return (true);
}

static int	game_on_key_down(int keycode, void *data)
{
	t_game	*game;

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

static int	game_on_key_up(int keycode, void *data)
{
	t_game	*game;

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

static int	game_on_close(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	game->controls_state.quit_requested = true;
	return (0);
}

static int	game_on_tick(void *data)
{
	t_game	*game;

	game = (t_game *)data;
	if (game->controls_state.quit_requested)
	{
		game_shutdown(game, EXIT_SUCCESS);
		return (0);
	}
	update_player_movement(&game->scene, &game->controls_state);
	render_scene(&game->scene, game->engine.window_size,
		&game->engine.buffer.px, &game->textures);
	mlx_put_image_to_window(game->engine.mlx_session, game->engine.mlx_window,
		game->engine.buffer.img, 0, 0);
	return (0);
}
