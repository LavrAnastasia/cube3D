#ifndef TEXTURES_INTERNAL_H
# define TEXTURES_INTERNAL_H

#include <mlx.h>
#include <stddef.h>
#include "textures_types.h"

void	*load_xpm(void *mlx_session, const char *path, t_dimensions *size);
char	*load_px_data(t_image_buffer *buffer);
void	texture_destroy(void *mlx_session, t_image_buffer *buffer);

#endif