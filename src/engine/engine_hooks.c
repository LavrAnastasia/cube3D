#include "engine_internal.h"

static int	handle_close(t_engine *engine)
{
	engine->events.on_close(engine->events.userdata);
	return (0);
}

static int	handle_loop(t_engine *engine)
{
	engine->events.on_tick(engine->events.userdata);
	return (0);
}

static int	handle_keypress(int keycode, t_engine *engine)
{
	engine->events.on_key_down(keycode, engine->events.userdata);
	return (0);
}

void	init_hooks(t_engine *engine)
{
	mlx_key_hook(engine->mlx_window, handle_keypress, engine);
	mlx_hook(engine->mlx_window, 17, 0, handle_close, engine);
	mlx_loop_hook(engine->mlx_session, handle_loop, engine);
}