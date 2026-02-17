/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:55:05 by audobnai          #+#    #+#             */
/*   Updated: 2025/05/13 18:14:45 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_try_add(int *count, int result)
{
	if (*count == -1 || result < 0)
		*count = -1;
	else
		*count += result;
}
