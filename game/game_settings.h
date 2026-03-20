/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_settings.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:48:49 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:48:50 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_SETTINGS_H
# define GAME_SETTINGS_H

# define FOV 60
# define GAME_TITLE "cub3D"

# ifdef __linux__
#  define MAX_WIN_WIDTH 1920
#  define MAX_WIN_HEIGHT 1080
# else
#  define MAX_WIN_WIDTH 1920
#  define MAX_WIN_HEIGHT 1080
# endif

#endif