#ifndef GAME_H
# define GAME_H

# include "map.h"

# define FOV 60
# define GAME_TITLE  "CUB3D"

typedef struct s_game
{
	void			*mlx_session;
	void			*mlx_window;
	char			**map;
	t_map_meta		map_meta;
    t_position      player_pos;
}	t_game;

#endif