/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:25:35 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 22:25:36 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "movement_inner.h"

void	update_player_movement(t_scene *scene, const t_controls_state *controls)
{
	const double current_time_seconds = get_current_time_seconds();
	const double frame_delta_seconds = get_frame_delta_seconds(
		current_time_seconds,
		scene->last_update_time_seconds
	);

	scene->last_update_time_seconds = current_time_seconds;
	update_player_angle(frame_delta_seconds, scene, controls);
	update_player_position(frame_delta_seconds, scene, controls);
}