#ifndef ENGINE_INTERNAL_H
# define ENGINE_INTERNAL_H

# include <mlx.h>
# include <stdlib.h>

# include "engine_types.h"
# include "engine_status.h"

void				init_hooks(t_engine *engine);
void				destroy_image_buffer(t_engine *engine);
void				clean_mlx_session(t_engine *engine);
t_engine_status		init_image_buffer(t_engine *engine);
t_engine_status		init_mlx(t_engine *engine, char *game_name);

#endif
