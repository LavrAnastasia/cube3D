#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "graphics_types.h"

int		graphics_load(t_graphics *graphics, void *mlx_session);
void	graphics_destroy(t_graphics *graphics, void *mlx_session);
void	graphics_put_pixel(t_px_buffer *px, int x, int y, t_color color);
t_color	graphics_get_pixel_color(t_px_buffer *buffer, int x, int y);

#endif
