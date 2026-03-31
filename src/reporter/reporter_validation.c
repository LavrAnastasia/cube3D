/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:13:18 by alavrukh          #+#    #+#             */
/*   Updated: 2026/03/27 16:21:18 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reporter_internal.h"

const char	*validation_msg(int code)
{
	static const char	*map[] = {
	[V_ERR_NO_INPUT_FILE] = "Please provide a .cub file",
	[V_ERR_ARG] = "Too many arguments provided, required: program + map",
	[V_ERR_EMPTY_FILE_NAME] = "File name must not be only .cub",
	[V_ERR_EXTENSION] = "Map must have .cub extension",
	};
	const int			size = sizeof(map) / sizeof(*map);

	if (code < 0 || code >= size)
		return (NULL);
	return (map[code]);
}
