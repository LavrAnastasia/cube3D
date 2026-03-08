#ifndef ENGINE_H
# define ENGINE_H

#include "types.h"
#include "textures_types.h"

typedef struct s_engine
{
	void			*mlx_session;
	void			*mlx_window;
	t_dimensions	window_size;
	t_image_buffer	buffer;
}	t_engine;

int		engine_init(t_engine *engine, char *game_name);
void    engine_shutdown(t_engine *engine);
void	engine_run(t_engine *engine);

#endif