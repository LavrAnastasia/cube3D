/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decode_bits_to_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:39:11 by audobnai          #+#    #+#             */
/*   Updated: 2025/07/15 19:39:15 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_decode_bits_to_char(int *bits)
{
	int				i;
	unsigned char	char_number;

	i = 0;
	char_number = 0;
	while (i < 8)
	{
		char_number = (char_number * 2) + bits[i];
		i++;
	}
	return (char_number);
}
