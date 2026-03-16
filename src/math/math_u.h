/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_u.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:58:55 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:58:56 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_U_H
# define MATH_U_H

# include <math.h>

// TODO: CHECK
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

double	deg_to_rad(double deg);
double	normalize_angle(double a);

#endif