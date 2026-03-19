/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:25:43 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 22:32:44 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_u.h"
#include "movement_inner.h"

void	update_player_angle(
	double frame_delta_seconds,
	t_scene *scene,
	const t_controls_state *controls
)
{
	const double	rotation_speed_per_second = 1.5;
	const double	rotation_step = rotation_speed_per_second
		* frame_delta_seconds;
	int				turn_step;

	turn_step = 0;
	if (controls->turn_left)
		turn_step--;
	if (controls->turn_right)
		turn_step++;
	if (turn_step)
	{
		scene->player.angle = normalize_angle(
				scene->player.angle + turn_step * rotation_step);
	}
}
