/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_status.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:49:00 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 19:49:01 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_STATUS_H
# define SCENE_STATUS_H

typedef enum e_scene_status
{
	SC_OK = 0,
	SC_ERR_MALLOC
}	t_scene_status;

#endif