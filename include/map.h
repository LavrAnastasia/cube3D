#ifndef MAP_H
# define MAP_H

# include "types.h"

typedef struct s_map_meta
{
	int			width;
	int			height;
}	t_map_meta;

typedef enum e_tile
{
	TILE_EMPTY = '0',
	TILE_WALL = '1'
}	t_tile;

#endif