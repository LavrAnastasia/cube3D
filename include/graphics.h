#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "sprites.h"

typedef struct s_graphics
{
	t_sprites	sprites;
	int			tile_size;

}	t_graphics;

int	graphics_load(t_graphics *graphics, void *mlx_session);
void	graphics_destroy(t_graphics *graphics, void *mlx_session);

#endif
