/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:40:38 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 22:40:39 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_TYPES_H
# define RAYCAST_TYPES_H

# include "types.h"

typedef enum e_ray_crossing
{
	R_CROSS_VERTICAL,
	R_CROSS_HORIZONTAL
}						t_ray_crossing;

typedef enum e_axis_x_direction
{
	X_LEFT,
	X_RIGHT,
	X_NONE
}						t_axis_x_direction;

typedef enum e_axis_y_direction
{
	Y_TOP,
	Y_BOTTOM,
	Y_NONE
}						t_axis_y_direction;

typedef struct s_axis_direction
{
	t_axis_x_direction	x;
	t_axis_y_direction	y;
}						t_axis_direction;

typedef struct s_ray_intersection
{
	t_point				point;
	t_ray_crossing		crossing;
	double				ray_length;
	t_vector			ray_direction;
	t_axis_direction	axis_direction;
}						t_ray_intersection;

#endif