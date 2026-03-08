#ifndef PIXELS_H
# define PIXELS_H

#include "textures_types.h"

void	pixels_put(t_px_buffer *px, int x, int y, t_color color);
t_color	pixels_get(const t_px_buffer *buffer, int x, int y);

#endif