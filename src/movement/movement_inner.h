/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_inner.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:25:39 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 22:27:15 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVEMENT_INNER_H
# define MOVEMENT_INNER_H

# include "controls_state.h"
# include "scene.h"

typedef struct s_move_intent
{
	int	x;
	int	y;
}		t_move_intent;

double	get_current_time_seconds(void);
double	get_frame_delta_seconds(
			double current_time_seconds,
			double last_update_time_seconds);
void	update_player_angle(
			double frame_delta_seconds,
			t_scene *scene,
			const t_controls_state *controls);
void	update_player_position(
			double frame_delta_seconds,
			t_scene *scene,
			const t_controls_state *controls);

#endif