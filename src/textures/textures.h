/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:46:52 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 20:46:53 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "textures_status.h"
# include "textures_types.h"

t_textures_status   textures_load(t_textures *textures, void *mlx_session, t_wall_texture_paths *paths);
void                textures_destroy(t_textures *textures, void *mlx_session);

#endif
