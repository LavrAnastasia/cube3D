/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:15:11 by audobnai          #+#    #+#             */
/*   Updated: 2025/05/13 17:19:15 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_int(const int n)
{
	char	*str;
	int		size;

	str = ft_itoa(n);
	if (!str)
		return (-1);
	size = ft_print_str(str);
	free(str);
	return (size);
}
