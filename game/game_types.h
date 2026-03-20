/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:48:54 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:48:55 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_TYPES_H
# define GAME_TYPES_H

# include "engine.h"
# include "controls_state.h"
# include "textures.h"
# include "scene.h"

typedef struct s_game
{
	t_engine			engine;
	t_textures			textures;
	t_scene				scene;
	t_controls_state	controls_state;
}	t_game;

#endif