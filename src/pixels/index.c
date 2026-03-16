/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:50:13 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 12:51:37 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures_types.h"

void	pixels_put(t_px_buffer *buffer, int x, int y, t_color color)
{
	char	*dst;

	dst = buffer->data + (y * buffer->line_len + x * (buffer->bpp / 8));
	*(t_color *)dst = color;
}

t_color	pixels_get(const t_px_buffer *buffer, int x, int y)
{
	t_color		color;
	const int	i = y * buffer->line_len + x * (buffer->bpp / 8);

	color = *(t_color *)(buffer->data + i);
	return (color);
}
