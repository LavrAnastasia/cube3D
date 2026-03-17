/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:51:07 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:52:37 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_internal.h"

static int	handle_close(t_engine *engine)
{
	if (engine->events.on_close)
		engine->events.on_close(engine->events.data);
	return (0);
}

static int	handle_loop(t_engine *engine)
{
	if (engine->events.on_tick)
		engine->events.on_tick(engine->events.data);
	return (0);
}

static int	handle_key_press(int keycode, t_engine *engine)
{
	if (engine->events.on_key_down)
		engine->events.on_key_down(keycode, engine->events.data);
	return (0);
}

static int	handle_key_release(int keycode, t_engine *engine)
{
	if (engine->events.on_key_up)
		engine->events.on_key_up(keycode, engine->events.data);
	return (0);
}

void	init_hooks(t_engine *engine)
{
	mlx_hook(engine->mlx_window, X11_KEY_PRESS_EVENT, X11_KEY_PRESS_MASK,
		handle_key_press, engine);
	mlx_hook(engine->mlx_window, X11_KEY_RELEASE_EVENT, X11_KEY_RELEASE_MASK,
		handle_key_release, engine);
	mlx_hook(engine->mlx_window, X11_DESTROY_NOTIFY_EVENT, 0, handle_close,
		engine);
	mlx_loop_hook(engine->mlx_session, handle_loop, engine);
}
