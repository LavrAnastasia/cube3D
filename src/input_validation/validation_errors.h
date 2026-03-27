/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_errors.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:52:43 by alavrukh          #+#    #+#             */
/*   Updated: 2026/03/27 15:52:44 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_ERRORS_H
# define VALIDATION_ERRORS_H

typedef enum e_validation_error_code
{
	V_ERR_NO_INPUT_FILE,
	V_ERR_ARG,
	V_ERR_EMPTY_FILE_NAME,
	V_ERR_EXTENSION
}	t_validation_error_code;

#endif