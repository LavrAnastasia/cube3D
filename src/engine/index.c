#include "engine_internal.h"

void engine_shutdown(t_engine *engine)
{
	destroy_image_buffer(engine);
    if (engine->mlx_session && engine->mlx_window)
	{
		mlx_destroy_window(engine->mlx_session, engine->mlx_window);
		engine->mlx_window = NULL;
	}
	if (engine->mlx_session)
	{
		clean_mlx_session(engine);
		engine->mlx_session = NULL;
	}
}

t_engine_status	engine_init(t_engine *engine, char *game_name)
{
	t_engine_status status;

	engine->buffer.size = engine->window_size;
	status = init_mlx(engine, game_name);
	if (status != ENGINE_OK)
	{
		engine_shutdown(engine);
		return (status);
	}
	status = init_image_buffer(engine);
	if (status != ENGINE_OK)
		engine_shutdown(engine);
	return (status);
}

void engine_run(t_engine *engine)
{
	init_hooks(engine);
	mlx_loop(engine->mlx_session);
}