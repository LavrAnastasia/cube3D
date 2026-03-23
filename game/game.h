/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:00:55 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:43:47 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "game_types.h"
# include "config.h"

bool	game_init(t_game *game, t_configuration *configuration);
void	game_shutdown(t_game *game, int exit_status);

#endif