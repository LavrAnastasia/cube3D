/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:51:09 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:51:10 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_INTERNAL_H
# define ENGINE_INTERNAL_H

# include "engine_status.h"
# include "engine_types.h"
# include <mlx.h>
# include <stdlib.h>

void			init_hooks(t_engine *engine);
void			destroy_image_buffer(t_engine *engine);
void			clean_mlx_session(t_engine *engine);
t_engine_status	init_image_buffer(t_engine *engine);
t_engine_status	init_mlx(t_engine *engine, char *game_name);

#endif
