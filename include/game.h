#ifndef GAME_H
# define GAME_H

# include "map.h"
# include "engine.h"
# include "graphics.h"

# define FOV 60
# define GAME_TITLE  "CUB3D"

typedef struct s_game
{
	t_engine		engine;
	t_graphics		graphics;
	// TODO: this is scene info
	char			**map;
	t_map_meta		map_meta;
	t_position      player_pos;
}	t_game;

# ifdef __linux__
#  define MAX_WIN_WIDTH 2560
#  define MAX_WIN_HEIGHT 1440
# else
#  define MAX_WIN_WIDTH 1920
#  define MAX_WIN_HEIGHT 1080
# endif

# define TILE_SIZE 64

#endif