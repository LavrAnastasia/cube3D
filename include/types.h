/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:01:07 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 23:06:02 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef unsigned int	t_color;

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_dimensions
{
	int	width;
	int	height;
}	t_dimensions;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

#endif