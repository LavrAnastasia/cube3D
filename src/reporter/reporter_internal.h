/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:21:31 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 17:21:32 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORTER_INTERNAL_H
# define REPORTER_INTERNAL_H

# include <stddef.h>

# include "render_error.h"
# include "reporter_types.h"
# include "engine_status.h"
# include "textures_status.h"
# include "scene_status.h"

const char	*render_msg(int code);

#endif