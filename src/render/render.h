#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include "textures.h"

void render_scene(t_scene *scene, t_dimensions window_size, t_px_buffer *buffer, const t_textures *textures);

#endif

