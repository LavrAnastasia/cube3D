#ifndef TEXTURES_H
# define TEXTURES_H

# include "textures_errors.h"
# include "textures_types.h"

t_textures_status   textures_load(t_textures *textures, void *mlx_session, const t_wall_texture_paths *paths);
void                textures_destroy(t_textures *textures, void *mlx_session);

#endif
