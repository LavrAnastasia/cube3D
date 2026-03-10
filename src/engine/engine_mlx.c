#include "engine_internal.h"

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

t_engine_status	init_image_buffer(t_engine *engine)
{
	engine->buffer.img = mlx_new_image(
		engine->mlx_session, engine->buffer.size.width, engine->buffer.size.height);
	if (!engine->buffer.img)
		return (ENGINE_ERR_CREATE_IMAGE);
	engine->buffer.px.data = mlx_get_data_addr(
		engine->buffer.img,
		&engine->buffer.px.bpp,
		&engine->buffer.px.line_len,
		&engine->buffer.px.endian);
	if (!engine->buffer.px.data)
		return (ENGINE_ERR_GET_IMAGE_DATA);
	return (ENGINE_OK);
}

void	destroy_image_buffer(t_engine *engine)
{
	if (engine->buffer.img)
		mlx_destroy_image(engine->mlx_session, engine->buffer.img);
	engine->buffer.img = NULL;
	engine->buffer.px.data = NULL;
}

t_engine_status	init_mlx(t_engine *engine, char *game_name)
{
	engine->mlx_session = mlx_init();
	if (!engine->mlx_session)
		return (ENGINE_ERR_INIT_MLX);
	engine->mlx_window = mlx_new_window(
			engine->mlx_session,
			engine->window_size.width,
			engine->window_size.height,
			game_name);
	if (!engine->mlx_window)
		return (ENGINE_ERR_CREATE_WINDOW);
	return (ENGINE_OK);
}