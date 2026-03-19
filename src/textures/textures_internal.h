/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:46:41 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 20:46:42 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_INTERNAL_H
# define TEXTURES_INTERNAL_H

# include "textures_types.h"
# include <mlx.h>
# include <stddef.h>

void	*load_xpm(void *mlx_session, const char *path, t_dimensions *size);
char	*load_px_data(t_image_buffer *buffer);
void	texture_destroy(void *mlx_session, t_image_buffer *buffer);

#endif