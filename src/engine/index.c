#include <stdlib.h>
#include <mlx.h>
#include "engine.h"

// TODO:  quitting should be handled by the game/app layer


// Private API

#ifdef __linux__

static void	clean_mlx_session(t_engine *engine)
{
	mlx_destroy_display(engine->mlx_session);
	free(engine->mlx_session);
}
#else

static void	clean_mlx_session(t_engine *engine)
{
	(void)(engine);
}
#endif

static int	init_image_buffer(t_engine *engine)
{
	engine->buffer.img = mlx_new_image(
		engine->mlx_session, engine->buffer.size.width, engine->buffer.size.height);
	if (!engine->buffer.img)
		return (0); // TODO: error
	engine->buffer.px.data = mlx_get_data_addr(
		engine->buffer.img,
		&engine->buffer.px.bpp,
		&engine->buffer.px.line_len,
		&engine->buffer.px.endian);
	if (!engine->buffer.px.data)
		return (0); // TODO: error
	return (1);
}

static void	destroy_image_buffer(t_engine *engine)
{
	if (engine->buffer.img)
		mlx_destroy_image(engine->mlx_session, engine->buffer.img);
	engine->buffer.img = NULL;
	engine->buffer.px.data = NULL;
}


static int	init_mlx(t_engine *engine, char *game_name)
{
	engine->mlx_session = mlx_init();
	if (!engine->mlx_session)
        return (0); // TODO: error
	engine->mlx_window = mlx_new_window(
			engine->mlx_session,
			engine->window_size.width,
			engine->window_size.height,
			game_name);
	if (!engine->mlx_window)
	    return (0); // TODO: error
    return (1); // TODO: succcess
}

// Public API

int	engine_init(t_engine *engine, char *game_name)
{
	engine->buffer.size = engine->window_size;
    if (!init_mlx(engine, game_name) || !init_image_buffer(engine))
    {
        engine_shutdown(engine);
        return (0); // TODO: error
    }
    return (1); // TODO: succcess
}

void engine_run(t_engine *engine)
{
	// TODO: Hooks
	// TODO: mlx_loop_hook
	mlx_loop(engine->mlx_session);
}

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