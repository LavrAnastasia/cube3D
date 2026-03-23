/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:48:47 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:48:48 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INTERNAL_H
# define GAME_INTERNAL_H

# include <stdbool.h>

# include "config.h"
# include "game_types.h"
# include "reporter.h"

bool	game_init_scene(t_scene *scene, t_configuration *configuration);
bool	game_init_engine(t_game *game);
bool	game_init_textures(
			t_textures *textures,
			t_configuration *configuration,
			void *mlx_session);
void	game_destroy_map(char **map);
void	game_shutdown(t_game *game, int exit_status);

#endif