/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:57:18 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:57:19 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_H
# define MAP_UTILS_H

# include "types.h"

int	is_in_bounds(t_point point, t_dimensions size);
int	is_wall(t_point point, char **map);
int	is_valid_char(char c);

#endif