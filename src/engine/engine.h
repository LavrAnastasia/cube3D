#ifndef ENGINE_H
# define ENGINE_H

# include "engine_types.h"
# include "engine_status.h"

t_engine_status	engine_init(t_engine *engine, char *game_name);
void    engine_shutdown(t_engine *engine);
void	engine_run(t_engine *engine);

#endif