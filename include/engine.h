#ifndef ENGINE_H
# define ENGINE_H

typedef struct s_engine
{
	void	*mlx_session;
	void	*mlx_window;
	int		window_width;
	int		window_height;		
}	t_engine;

int		engine_init(t_engine *engine, char *game_name);
void    engine_shutdown(t_engine *engine);
void	engine_run(t_engine *engine);

#endif