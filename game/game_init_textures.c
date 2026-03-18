/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:11 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 20:52:01 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "config.h"

bool game_init_textures(t_textures *textures, t_configuration *configuration, void *mlx_session)
{
	if (textures_load(textures, mlx_session, &configuration->samples.paths) != TEX_OK)
		return (false);
  return (true);
}