/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_status.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 20:46:46 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 20:46:47 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_STATUS_H
# define TEXTURES_STATUS_H

typedef enum e_textures_status
{
	TEX_OK = 0,
	TEX_ERR_LOAD_IMAGE,
	TEX_ERR_LOAD_PIXELS
}	t_textures_status;

#endif