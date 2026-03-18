/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 22:25:45 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 22:31:22 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>

double	get_current_time_seconds(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((double)current_time.tv_sec + (double)current_time.tv_usec
		/ 1000000.0);
}

double	get_frame_delta_seconds(
	double current_time_seconds,
	double last_update_time_seconds
)
{
	double	frame_delta_seconds;

	if (last_update_time_seconds == 0.0)
		return (0.0);
	frame_delta_seconds = current_time_seconds - last_update_time_seconds;
	if (frame_delta_seconds < 0.0)
		return (0.0);
	if (frame_delta_seconds > 0.1)
		return (0.1);
	return (frame_delta_seconds);
}
