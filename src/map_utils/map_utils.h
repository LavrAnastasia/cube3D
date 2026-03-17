/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:57:18 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/17 19:39:53 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

# include "types.h"

int	is_in_bounds(t_point point, t_dimensions size);
int	is_wall(t_point point, char **map);
int	is_valid_char(char c);
int is_player_pos(char c);

#endif