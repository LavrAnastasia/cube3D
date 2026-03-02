#include <stdlib.h> // TODO: delete, uses for exit func
#include <mlx.h>
#include "engine.h"

// TODO: think about it 
// Previously, the game had a single exit function.
// Should quitting be handled by the engine, or by the game/app layer?


// Private API

#ifdef __linux__

void	clean_mlx_session(t_engine *engine)
{
	mlx_destroy_display(engine->mlx_session);
	free(engine->mlx_session);
}
#else

void	clean_mlx_session(t_engine *engine)
{
	(void)(engine);
}
#endif


static int	init_mlx(t_engine *engine, char *game_name)
{
	engine->mlx_session = mlx_init();
	if (!engine->mlx_session)
        return (0); // TODO: error
	engine->mlx_window = mlx_new_window(
			engine->mlx_session,
			engine->window_width,
			engine->window_height,
			game_name);
	if (!engine->mlx_window)
	    return (0); // TODO: error
    return (1); // TODO: succcess
}

// Public API

int	engine_init(t_engine *engine, char *game_name)
{
    if (!init_mlx(engine, game_name))
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
    if (engine->mlx_session && engine->mlx_window)
		mlx_destroy_window(engine->mlx_session, engine->mlx_window);
	if (engine->mlx_session)
		clean_mlx_session(engine);
}