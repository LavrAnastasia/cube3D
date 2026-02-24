# include <mlx.h>
# include "graphics.h"

static void	*load_xpm(void *mlx_session, const char *path, int size)
{
	return (
		mlx_xpm_file_to_image(
			mlx_session,
			(char *)path,
			&size,
			&size
		)
	);
}

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