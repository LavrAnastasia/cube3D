/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:58:53 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:59:44 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_u.h"

double	deg_to_rad(double deg)
{
	return (deg * M_PI / 180.0);
}

double	normalize_angle(double angle)
{
	const double	two_pi = 2.0 * M_PI;

	while (angle < 0.0)
		angle += two_pi;
	while (angle >= two_pi)
		angle -= two_pi;
	return (angle);
}
