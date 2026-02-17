/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:17:18 by audobnai          #+#    #+#             */
/*   Updated: 2025/05/13 13:17:20 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex(unsigned int num, int uppercase, int leading_zero)
{
	char	str[9];
	char	*base;
	int		i;
	size_t	first_digit;

	if (num == 0 && !leading_zero)
		return (ft_print_char('0'));
	i = 8;
	base = "0123456789abcdef";
	if (uppercase)
		base = "0123456789ABCDEF";
	str[i--] = '\0';
	while (num && (i >= 0))
	{
		str[i--] = base[num % 16];
		num /= 16;
	}
	first_digit = i + 1;
	if (leading_zero)
	{
		ft_memset(str, '0', first_digit);
		first_digit = 0;
	}
	return (ft_print_str(str + first_digit));
}
