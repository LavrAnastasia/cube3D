/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:51:20 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:51:21 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include "engine_status.h"
# include "engine_types.h"

t_engine_status	engine_init(t_engine *engine, char *game_name);
void			engine_shutdown(t_engine *engine);
void			engine_run(t_engine *engine);

#endif