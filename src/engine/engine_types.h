#ifndef ENGINE_TYPES_H
# define ENGINE_TYPES_H

#include "types.h"
#include "textures_types.h"

#define X11_KEY_PRESS_EVENT 2
#define X11_KEY_RELEASE_EVENT 3
#define X11_KEY_PRESS_MASK (1L << 0)
#define X11_KEY_RELEASE_MASK (1L << 1)
#define X11_DESTROY_NOTIFY_EVENT 17

typedef struct s_engine_events
{
	int		(*on_key_down)(int keycode, void *data);
    int		(*on_key_up)(int keycode, void *data);
	int		(*on_close)(void *data);
	int		(*on_tick)(void *data);
	void	*data;
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