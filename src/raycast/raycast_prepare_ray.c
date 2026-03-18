/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_prepare_ray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:40:34 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 22:56:09 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast_internal.h"

static t_axis_direction	calc_axis_direction(
							double ray_direction_x,
							double ray_direction_y);

t_ray_info	make_ray_info(double angle)
{
	const t_vector	ray_direction = (t_vector){
		.x = cos(angle),
		.y = sin(angle)};

	return ((t_ray_info){.direction = ray_direction,
		.axis_direction = calc_axis_direction(ray_direction.x,
			ray_direction.y)});
}

static t_axis_direction	calc_axis_direction(
	double ray_direction_x,
	double ray_direction_y
)
{
	const double		eps = 1e-9;
	t_axis_direction	direction;

	direction.x = X_NONE;
	direction.y = Y_NONE;
	if (ray_direction_x < -eps)
		direction.x = X_LEFT;
	else if (ray_direction_x > eps)
		direction.x = X_RIGHT;
	if (ray_direction_y < -eps)
		direction.y = Y_TOP;
	else if (ray_direction_y > eps)
		direction.y = Y_BOTTOM;
	return (direction);
}
