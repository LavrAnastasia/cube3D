/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_projection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:16:34 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 17:42:35 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static double	correct_fisheye_distance(double ray_length, double angle_diff)
{
	const double	perp_distance = ray_length * cos(angle_diff);

	if (perp_distance < EPS_DIST)
		return (EPS_DIST);
	return (perp_distance);
}

static double	calc_wall_height(
	double distance,
	t_dimensions window_size,
	double scale)
{
	return ((((double)window_size.width * 0.5) / scale) / distance);
}

static double	calc_wall_top(double wall_height, size_t window_height)
{
	return ((window_height / 2.0) - (wall_height / 2.0));
}

static t_range	calc_wall_range(double wall_height, t_dimensions window_size)
{
	double	top;
	double	bottom;

	top = calc_wall_top(wall_height, (size_t)window_size.height);
	bottom = top + wall_height;
	if (top < 0)
		top = 0;
	if (bottom > (double)window_size.height)
		bottom = window_size.height;
	return ((t_range){.start = (size_t)top, .end = (size_t)bottom});
}

t_wall_projection	make_wall_projection(
	double ray_length,
	double angle_diff,
	t_dimensions window_size,
	double scale)
{
	const double	perp_distance = correct_fisheye_distance(ray_length,
			angle_diff);
	const double	wall_height = calc_wall_height(perp_distance, window_size,
			scale);

	return ((t_wall_projection){.range = calc_wall_range(wall_height,
			window_size), .top = calc_wall_top(wall_height,
			(size_t)window_size.height), .height = wall_height});
}
