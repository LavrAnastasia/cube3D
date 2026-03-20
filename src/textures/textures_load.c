/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:46:43 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 15:41:36 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures_internal.h"

void	*load_xpm(void *mlx_session, const char *path, t_dimensions *size)
{
	return (mlx_xpm_file_to_image(mlx_session, (char *)path, &size->width,
			&size->height));
}

char	*load_px_data(t_image_buffer *buffer)
{
	return (mlx_get_data_addr(buffer->img, &buffer->px.bpp,
			&buffer->px.line_len, &buffer->px.endian));
}
