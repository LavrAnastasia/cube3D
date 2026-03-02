#ifndef ENGINE_H
# define ENGINE_H

typedef struct s_image_buffer
{
	void	*img;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image_buffer;

typedef struct s_engine
{
	void			*mlx_session;
	void			*mlx_window;
	int				window_width;
	int				window_height;
	t_image_buffer	buffer;
}	t_engine;

int		engine_init(t_engine *engine, char *game_name);
void    engine_shutdown(t_engine *engine);
void	engine_run(t_engine *engine);

#endif