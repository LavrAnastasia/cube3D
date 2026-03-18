/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:57:18 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 22:21:50 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

# include "map_utils_internal.h"

bool	is_in_bounds(t_point point, char **map, t_dimensions size);
bool	is_wall(t_point point, char **map);
bool	is_valid_char(char c);
bool	is_player_pos(char c);

#endif