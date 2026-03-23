/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:21:04 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 17:21:05 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_ERROR_H
# define RENDER_ERROR_H

typedef enum e_render_error
{
	RENDER_ERR_RAY_INTERSECTION = 0,
	RENDER_ERR_FALLBACK
}	t_render_error;

#endif