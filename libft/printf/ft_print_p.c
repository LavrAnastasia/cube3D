/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:15:40 by audobnai          #+#    #+#             */
/*   Updated: 2025/05/13 17:20:58 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_p(const uintptr_t ptr)
{
	int				size;
	unsigned int	low;
	unsigned int	high;

	low = (unsigned int)(ptr & 0xFFFFFFFF);
	high = (unsigned int)((ptr >> 32) & 0xFFFFFFFF);
	if (!high && !low)
		return (ft_print_str("(nil)"));
	size = ft_print_str("0x");
	if (high != 0)
		ft_try_add(&size, ft_puthex(high, 0, 0));
	ft_try_add(&size, ft_puthex(low, 0, high != 0));
	return (size);
}
