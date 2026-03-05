#include <mlx.h>
#include <stddef.h>
#include "graphics_types.h"

void	*load_xpm(void *mlx_session, const char *path, t_dimensions *size);
void	graphics_destroy(t_graphics *graphics, void *mlx_session);

int	graphics_load(t_graphics *graphics, void *mlx_session)
{
    
    // TODO: read from real config
    const char *NO =  "resources/no.xpm";
    const char *SO =  "resources/so.xpm";
    const char *EA =  "resources/ea.xpm";
    const char *WE =  "resources/we.xpm";

    graphics->sprites.north_texture.img = load_xpm(mlx_session, NO, &graphics->sprites.north_texture.size);
    graphics->sprites.south_texture.img = load_xpm(mlx_session, SO, &graphics->sprites.south_texture.size);
	graphics->sprites.east_texture.img = load_xpm(mlx_session, EA, &graphics->sprites.east_texture.size);
	graphics->sprites.west_texture.img = load_xpm(mlx_session, WE, &graphics->sprites.west_texture.size);
    if (!graphics->sprites.north_texture.img
        || !graphics->sprites.south_texture.img
		|| !graphics->sprites.east_texture.img
		|| !graphics->sprites.west_texture.img)
	{
		graphics_destroy(graphics, mlx_session);
		return (0); // TODO: error
	}

	graphics->sprites.north_texture.px.data = mlx_get_data_addr(
		graphics->sprites.north_texture.img,
		&graphics->sprites.north_texture.px.bpp,
		&graphics->sprites.north_texture.px.line_len,
		&graphics->sprites.north_texture.px.endian);

	graphics->sprites.south_texture.px.data = mlx_get_data_addr(
		graphics->sprites.south_texture.img,
		&graphics->sprites.south_texture.px.bpp,
		&graphics->sprites.south_texture.px.line_len,
		&graphics->sprites.south_texture.px.endian);

	graphics->sprites.east_texture.px.data = mlx_get_data_addr(
		graphics->sprites.east_texture.img,
		&graphics->sprites.east_texture.px.bpp,
		&graphics->sprites.east_texture.px.line_len,
		&graphics->sprites.east_texture.px.endian);

	graphics->sprites.west_texture.px.data = mlx_get_data_addr(
		graphics->sprites.west_texture.img,
		&graphics->sprites.west_texture.px.bpp,
		&graphics->sprites.west_texture.px.line_len,
		&graphics->sprites.west_texture.px.endian);

	if (!graphics->sprites.north_texture.px.data
        || !graphics->sprites.south_texture.px.data
		|| !graphics->sprites.east_texture.px.data
		|| !graphics->sprites.west_texture.px.data)
	{
		graphics_destroy(graphics, mlx_session);
		return (0); // TODO: error
	}
	
    return (1); // // TODO: success
}

void	graphics_put_pixel(t_px_buffer *buffer, int x, int y, t_color color)
{
	char *dst;
    
    dst = buffer->data + (y * buffer->line_len + x * (buffer->bpp / 8));
	*(t_color *)dst = color;
}


t_color graphics_get_pixel_color(t_px_buffer *buffer, int x, int y)
{
	t_color		color;
	const int	i = y * buffer->line_len + x * (buffer->bpp / 8);

	color = *(t_color *)(buffer->data + i);
	return (color);
}

void	graphics_destroy(t_graphics *graphics, void *mlx_session)
{
	if (graphics->sprites.north_texture.img)
	{
		mlx_destroy_image(mlx_session, graphics->sprites.north_texture.img);
		graphics->sprites.north_texture.img = NULL;
		graphics->sprites.north_texture.px.data = NULL;
	}
	if (graphics->sprites.south_texture.img)
	{
		mlx_destroy_image(mlx_session, graphics->sprites.south_texture.img);
		graphics->sprites.south_texture.img = NULL;
		graphics->sprites.south_texture.px.data = NULL;
	}
	if (graphics->sprites.east_texture.img)
	{
		mlx_destroy_image(mlx_session, graphics->sprites.east_texture.img);
		graphics->sprites.east_texture.img = NULL;
		graphics->sprites.east_texture.px.data = NULL;
	}
	if (graphics->sprites.west_texture.img)
	{
		mlx_destroy_image(mlx_session, graphics->sprites.west_texture.img);
		graphics->sprites.west_texture.img = NULL;
		graphics->sprites.west_texture.px.data = NULL;
	}
}