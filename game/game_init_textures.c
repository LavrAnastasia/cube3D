/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:51:11 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:37:23 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_internal.h"

bool	game_init_textures(
	t_textures *textures,
	t_configuration *configuration,
	void *mlx_session
)
{
	const t_textures_status	status = textures_init(textures, mlx_session,
			&configuration->samples.paths);

	if (status != TEX_OK)
	{
		report(D_TEXTURES, status, SL_ERROR);
		return (false);
	}
	return (true);
}
