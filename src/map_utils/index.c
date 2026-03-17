/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:57:16 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:57:17 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "types.h"

int	is_in_bounds(t_point point, t_dimensions size)
{
	return (point.x >= 0 && point.x < size.width && point.y >= 0
		&& point.y < size.height);
}

int	is_wall(t_point point, char **map)
{
	return (map[point.y][point.x] == TILE_WALL);
}

int	is_valid_char(char c)
{
	return (c == TILE_EMPTY || c == TILE_WALL || c == TILE_PLAYER_NORTH
		|| c == TILE_PLAYER_EAST || c == TILE_PLAYER_SOURTH
		|| c == TILE_PLAYER_WEST);
}
