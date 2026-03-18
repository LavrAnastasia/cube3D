/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:46:38 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 20:46:39 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "textures_internal.h"

void texture_destroy(void *mlx_session, t_image_buffer *buffer)
{
	if (buffer->img == NULL)
		return;
	mlx_destroy_image(mlx_session, buffer->img);
	buffer->img = NULL;
	buffer->px.data = NULL;
}