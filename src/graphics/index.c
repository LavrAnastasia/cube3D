#include <mlx.h>
#include <stddef.h>
#include "graphics_types.h"

void	*load_xpm(void *mlx_session, const char *path, t_dimensions *size);
char	*load_px_data(t_image_buffer *buffer);
void	graphics_destroy(t_textures *textures, void *mlx_session);

int	graphics_load(t_textures *textures, void *mlx_session)
{
    
    // TODO: read from real config
    const char *NO =  "resources/no.xpm";
    const char *SO =  "resources/so.xpm";
    const char *EA =  "resources/ea.xpm";
    const char *WE =  "resources/we.xpm";

    textures->wall.north.img = load_xpm(mlx_session, NO, &textures->wall.north.size);
    textures->wall.south.img = load_xpm(mlx_session, SO, &textures->wall.south.size);
	textures->wall.east.img = load_xpm(mlx_session, EA, &textures->wall.east.size);
	textures->wall.west.img = load_xpm(mlx_session, WE, &textures->wall.west.size);
    if (!textures->wall.north.img
        || !textures->wall.south.img
		|| !textures->wall.east.img
		|| !textures->wall.west.img)
	{
		graphics_destroy(textures, mlx_session);
		return (0); // TODO: error
	}

	textures->wall.north.px.data = load_px_data(&textures->wall.north);
	textures->wall.south.px.data = load_px_data(&textures->wall.south);
	textures->wall.east.px.data = load_px_data(&textures->wall.east);
	textures->wall.west.px.data = load_px_data(&textures->wall.west);

	if (!textures->wall.north.px.data
        || !textures->wall.south.px.data
		|| !textures->wall.east.px.data
		|| !textures->wall.west.px.data)
	{
		graphics_destroy(textures, mlx_session);
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

void	graphics_destroy(t_textures *textures, void *mlx_session)
{
	if (textures->wall.north.img)
	{
		mlx_destroy_image(mlx_session, textures->wall.north.img);
		textures->wall.north.img = NULL;
		textures->wall.north.px.data = NULL;
	}
	if (textures->wall.south.img)
	{
		mlx_destroy_image(mlx_session, textures->wall.south.img);
		textures->wall.south.img = NULL;
		textures->wall.south.px.data = NULL;
	}
	if (textures->wall.east.img)
	{
		mlx_destroy_image(mlx_session, textures->wall.east.img);
		textures->wall.east.img = NULL;
		textures->wall.east.px.data = NULL;
	}
	if (textures->wall.west.img)
	{
		mlx_destroy_image(mlx_session, textures->wall.west.img);
		textures->wall.west.img = NULL;
		textures->wall.west.px.data = NULL;
	}
}