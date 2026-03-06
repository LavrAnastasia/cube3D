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

    textures->sprites.north_texture.img = load_xpm(mlx_session, NO, &textures->sprites.north_texture.size);
    textures->sprites.south_texture.img = load_xpm(mlx_session, SO, &textures->sprites.south_texture.size);
	textures->sprites.east_texture.img = load_xpm(mlx_session, EA, &textures->sprites.east_texture.size);
	textures->sprites.west_texture.img = load_xpm(mlx_session, WE, &textures->sprites.west_texture.size);
    if (!textures->sprites.north_texture.img
        || !textures->sprites.south_texture.img
		|| !textures->sprites.east_texture.img
		|| !textures->sprites.west_texture.img)
	{
		graphics_destroy(textures, mlx_session);
		return (0); // TODO: error
	}

	textures->sprites.north_texture.px.data = load_px_data(&textures->sprites.north_texture);
	textures->sprites.south_texture.px.data = load_px_data(&textures->sprites.south_texture);
	textures->sprites.east_texture.px.data = load_px_data(&textures->sprites.east_texture);
	textures->sprites.west_texture.px.data = load_px_data(&textures->sprites.west_texture);

	if (!textures->sprites.north_texture.px.data
        || !textures->sprites.south_texture.px.data
		|| !textures->sprites.east_texture.px.data
		|| !textures->sprites.west_texture.px.data)
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
	if (textures->sprites.north_texture.img)
	{
		mlx_destroy_image(mlx_session, textures->sprites.north_texture.img);
		textures->sprites.north_texture.img = NULL;
		textures->sprites.north_texture.px.data = NULL;
	}
	if (textures->sprites.south_texture.img)
	{
		mlx_destroy_image(mlx_session, textures->sprites.south_texture.img);
		textures->sprites.south_texture.img = NULL;
		textures->sprites.south_texture.px.data = NULL;
	}
	if (textures->sprites.east_texture.img)
	{
		mlx_destroy_image(mlx_session, textures->sprites.east_texture.img);
		textures->sprites.east_texture.img = NULL;
		textures->sprites.east_texture.px.data = NULL;
	}
	if (textures->sprites.west_texture.img)
	{
		mlx_destroy_image(mlx_session, textures->sprites.west_texture.img);
		textures->sprites.west_texture.img = NULL;
		textures->sprites.west_texture.px.data = NULL;
	}
}