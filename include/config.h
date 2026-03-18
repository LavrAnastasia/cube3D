/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:00:49 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/19 16:50:51 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "colors.h"
# include "map.h"
# include "textures_types.h"

typedef struct s_config
{
	t_wall_texture_paths	paths;
	t_rgb					floor;
	t_rgb					ceiling;
	int seen_floor;
	int seen_ceiling;
}	t_config;

typedef struct s_configuration
{
	char			**map;
	t_dimensions	map_size;
	t_position		player_pos;
	t_player_tile	player_start;
	t_config		samples;
}	t_configuration;
#endif 