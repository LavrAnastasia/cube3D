/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_types.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:52:49 by alavrukh          #+#    #+#             */
/*   Updated: 2026/03/27 15:52:50 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_TYPES_H
# define VALIDATION_TYPES_H

# include "validation_errors.h"
# include <stdbool.h>

typedef struct s_validation_result
{
	bool					ok;
	t_validation_error_code	error_code;
}							t_validation_result;

#endif