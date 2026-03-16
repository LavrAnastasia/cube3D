/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:50:20 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 12:50:21 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELS_H
# define PIXELS_H

# include "textures_types.h"

void	pixels_put(t_px_buffer *px, int x, int y, t_color color);
t_color	pixels_get(const t_px_buffer *buffer, int x, int y);

#endif