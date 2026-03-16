#ifndef MAP_H
# define MAP_H

typedef enum e_tile
{
	TILE_EMPTY = '0',
	TILE_WALL = '1'
}	t_tile;

typedef enum e_player_tile
{
	TILE_PLAYER_NORTH = 'N',
	TILE_PLAYER_WEST = 'W',
	TILE_PLAYER_SOURTH = 'S',
	TILE_PLAYER_EAST = 'E'
} t_player_tile;

#endif