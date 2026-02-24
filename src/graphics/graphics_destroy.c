# include <mlx.h>
# include "graphics.h"

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