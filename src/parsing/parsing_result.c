/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_result.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:39:53 by alavrukh          #+#    #+#             */
/*   Updated: 2026/03/27 15:43:28 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

t_parse_result	make_parse_success_result(void)
{
	return ((t_parse_result){.ok = true});
}

t_parse_result	make_parse_error_result(t_parse_error_code code,
		const char *info)
{
	return ((t_parse_result){.ok = false, .error = (t_parse_error){.code = code,
		.info = info}});
}
