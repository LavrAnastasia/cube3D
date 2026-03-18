/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:57:16 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 20:35:00 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map_utils_internal.h"
#include "map.h"

bool	is_in_bounds(t_point point, char **map, t_dimensions size)
{
	if (point.y >= 0 && point.y < size.height && point.x >= 0)
	{
		return (point.x < (int)ft_strlen(map[point.y]));
	}
	else
		return (false);
}

int	is_wall(t_point point, char **map)
{
	return (map[point.y][point.x] == TILE_WALL);
}

int is_player_pos(char c)
{
	return (c == TILE_PLAYER_NORTH
		|| c == TILE_PLAYER_EAST || c == TILE_PLAYER_SOURTH
		|| c == TILE_PLAYER_WEST);
}

int	is_valid_char(char c)
{
	return (c == TILE_EMPTY || c == TILE_WALL || is_player_pos(c));
}
