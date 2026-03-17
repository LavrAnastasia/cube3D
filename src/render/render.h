/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:17:38 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 12:46:57 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "scene.h"
# include "textures.h"

void	render_scene(
			const t_scene *scene,
			t_dimensions window_size,
			t_px_buffer *buffer,
			const t_textures *textures);

#endif
