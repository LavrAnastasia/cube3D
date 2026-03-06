#include "textures_internal.h"

void	textures_destroy(t_textures *textures, void *mlx_session);

int	textures_load(t_textures *textures, void *mlx_session, t_wall_texture_paths *paths)
{
    textures->wall.north.img = load_xpm(mlx_session, paths->north, &textures->wall.north.size);
    textures->wall.south.img = load_xpm(mlx_session, paths->south, &textures->wall.south.size);
	textures->wall.east.img = load_xpm(mlx_session, paths->east, &textures->wall.east.size);
	textures->wall.west.img = load_xpm(mlx_session, paths->west, &textures->wall.west.size);

    if (!textures->wall.north.img || !textures->wall.south.img
		|| !textures->wall.east.img || !textures->wall.west.img)
	{
		textures_destroy(textures, mlx_session);
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
		textures_destroy(textures, mlx_session);
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

void	textures_destroy(t_textures *textures, void *mlx_session)
{
	texture_destroy(mlx_session, &textures->wall.north);
	texture_destroy(mlx_session, &textures->wall.south);
	texture_destroy(mlx_session, &textures->wall.east);
	texture_destroy(mlx_session, &textures->wall.west);
}