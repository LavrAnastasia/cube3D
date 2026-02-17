/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:16:17 by audobnai          #+#    #+#             */
/*   Updated: 2025/05/13 17:24:11 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_uint(const unsigned int un)
{
	char	*str;
	int		size;

	str = ft_utoa(un);
	if (!str)
		return (-1);
	size = ft_print_str(str);
	free(str);
	return (size);
}
