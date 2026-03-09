#ifndef ENGINE_TYPES_H
# define ENGINE_TYPES_H

#include "types.h"
#include "textures_types.h"

typedef struct s_engine_events
{
	int		(*on_key_down)(int keycode, void *userdata);
	int		(*on_close)(void *userdata);
	int		(*on_tick)(void *userdata);
	void	*userdata;
}	t_engine_events;

typedef struct s_engine
{
	void			*mlx_session;
	void			*mlx_window;
	t_dimensions	window_size;
	t_image_buffer	buffer;
	t_engine_events	events;
}	t_engine;

#endif