/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:48:44 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:53:31 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_internal.h"

bool	game_init(t_game *game, t_configuration *configuration)
{
	if (!game_init_scene(&game->scene, configuration))
		return (false);
	if (!game_init_engine(game))
		return (false);
	if (!game_init_textures(&game->textures, configuration,
			game->engine.mlx_session))
		return (false);
	return (true);
}
