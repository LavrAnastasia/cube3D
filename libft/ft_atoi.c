/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:32:57 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/24 18:06:22 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	long	number;
	size_t	i;

	number = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	sign = 1;
	if ((nptr[i] == '+' || nptr[i] == '-'))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		number = (number * 10) + (nptr[i] - '0');
		if (sign == 1 && number > INT_MAX)
			return (INT_MAX);
		else if (sign == -1 && (-number) < INT_MIN)
			return (INT_MIN);
		i++;
	}
	return ((int)(number * sign));
}
