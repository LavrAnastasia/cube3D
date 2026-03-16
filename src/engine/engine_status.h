/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_status.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 14:51:14 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/16 14:51:15 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_STATUS_H
# define ENGINE_STATUS_H

typedef enum e_engine_status
{
	ENGINE_OK = 0,
	ENGINE_ERR_INIT_MLX,
	ENGINE_ERR_CREATE_WINDOW,
	ENGINE_ERR_CREATE_IMAGE,
	ENGINE_ERR_GET_IMAGE_DATA
}	t_engine_status;

#endif