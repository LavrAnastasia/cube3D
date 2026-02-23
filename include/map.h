#ifndef MAP_H
# define MAP_H

# include "sprites.h"

# define TILE_SIZE 64

typedef struct s_map_meta
{
	int			width;
	int			height;
    t_sprites	sprites;
}	t_map_meta;

typedef enum e_tile
{
	TILE_EMPTY = '0',
	TILE_WALL = '1'
}	t_tile;

# ifdef __linux__
#  define MAX_WIN_WIDTH 2560
#  define MAX_WIN_HEIGHT 1440
# else
#  define MAX_WIN_WIDTH 1920
#  define MAX_WIN_HEIGHT 1080
# endif

#endif