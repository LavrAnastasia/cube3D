#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "sprites.h"
# include "graphics_types.h"
# include "types.h"

typedef struct s_graphics
{
	t_sprites	sprites;
	int			tile_size;
}	t_graphics;

int		graphics_load(t_graphics *graphics, void *mlx_session);
void	graphics_destroy(t_graphics *graphics, void *mlx_session);
void	put_pixel(t_px_buffer *px, int x, int y, t_color color);

#endif
