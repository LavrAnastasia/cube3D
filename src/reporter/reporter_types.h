/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:21:33 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/26 19:01:58 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORTER_TYPES_H
# define REPORTER_TYPES_H

typedef enum e_reporter_domain
{
	D_ENGINE = 0,
	D_SCENE,
	D_TEXTURES,
	D_RENDER,
	D_VALIDATION
}	t_reporter_domain;

typedef enum e_severity_level
{
	SL_WARNING = 0,
	SL_ERROR
}	t_severity_level;

#endif