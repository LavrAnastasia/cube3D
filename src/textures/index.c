#include "textures_internal.h"
#include "textures_status.h"

void	textures_destroy(t_textures *textures, void *mlx_session)
{
	texture_destroy(mlx_session, &textures->wall.north);
	texture_destroy(mlx_session, &textures->wall.south);
	texture_destroy(mlx_session, &textures->wall.east);
	texture_destroy(mlx_session, &textures->wall.west);
}

static void load_wall_textures(t_textures *textures, void *mlx_session, t_wall_texture_paths *paths)
{
	textures->wall.north.img = load_xpm(mlx_session, paths->north, &textures->wall.north.size);
    textures->wall.south.img = load_xpm(mlx_session, paths->south, &textures->wall.south.size);
	textures->wall.east.img = load_xpm(mlx_session, paths->east, &textures->wall.east.size);
	textures->wall.west.img = load_xpm(mlx_session, paths->west, &textures->wall.west.size);
}

static void load_wall_pixels(t_textures *textures)
{
	textures->wall.north.px.data = load_px_data(&textures->wall.north);
	textures->wall.south.px.data = load_px_data(&textures->wall.south);
	textures->wall.east.px.data = load_px_data(&textures->wall.east);
	textures->wall.west.px.data = load_px_data(&textures->wall.west);
}

t_textures_status	textures_load(t_textures *textures, void *mlx_session, t_wall_texture_paths *paths)
{
    load_wall_textures(textures, mlx_session, paths);
    if (!textures->wall.north.img || !textures->wall.south.img
		|| !textures->wall.east.img || !textures->wall.west.img)
	{
		textures_destroy(textures, mlx_session);
		return (TEX_ERR_LOAD_IMAGE);
	}
	load_wall_pixels(textures);
	if (!textures->wall.north.px.data || !textures->wall.south.px.data
		|| !textures->wall.east.px.data || !textures->wall.west.px.data)
	{
		textures_destroy(textures, mlx_session);
		return (TEX_ERR_LOAD_PIXELS);
	}
    return (TEX_OK);
}