#ifndef TEXTURES_H
# define TEXTURES_H

# include "textures_types.h"

int		textures_load(t_textures *textures, void *mlx_session, t_wall_texture_paths *paths);
void	textures_destroy(t_textures *textures, void *mlx_session);

#endif
