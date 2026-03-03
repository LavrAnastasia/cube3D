# include <mlx.h>
#include "graphics.h"

void	*load_xpm(void *mlx_session, const char *path, int size);

int	graphics_load(t_graphics *graphics, void *mlx_session)
{
    const int size = graphics->tile_size;
    
    // TODO: read from real config
    const char *NO =  "resources/no.xpm";
    const char *SO =  "resources/so.xpm";
    const char *EA =  "resources/ea.xpm";
    const char *WE =  "resources/we.xpm";

    graphics->sprites.north_texture = load_xpm(mlx_session, NO, size);
    graphics->sprites.south_texture = load_xpm(mlx_session, SO, size);
	graphics->sprites.east_texture = load_xpm(mlx_session, EA, size);
	graphics->sprites.west_texture = load_xpm(mlx_session, WE, size);
    if (!graphics->sprites.north_texture
        || !graphics->sprites.south_texture
		|| !graphics->sprites.east_texture
		|| !graphics->sprites.west_texture)
        return (0); // TODO: error
    return (1); // // TODO: success
}

void	put_pixel(t_px_buffer *buffer, int x, int y, t_color color)
{
	char *dst;
    
    dst = buffer->data + (y * buffer->line_len + x * (buffer->bpp / 8));
	*(t_color *)dst = color;
}

void	graphics_destroy(t_graphics *graphics, void *mlx_session)
{
	if (graphics->sprites.north_texture)
		mlx_destroy_image(mlx_session, graphics->sprites.north_texture);
	if (graphics->sprites.south_texture)
		mlx_destroy_image(mlx_session, graphics->sprites.south_texture);
	if (graphics->sprites.east_texture)
		mlx_destroy_image(mlx_session, graphics->sprites.east_texture);
	if (graphics->sprites.west_texture)
		mlx_destroy_image(mlx_session, graphics->sprites.west_texture);
}