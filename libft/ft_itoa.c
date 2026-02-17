/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:43:15 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:23:23 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoasize(long n)
{
	size_t	alloc_size;

	alloc_size = 0;
	if (n <= 0)
		alloc_size += 1;
	if (n < 0)
		n *= -1;
	while (n)
	{
		alloc_size += 1;
		n /= 10;
	}
	return (alloc_size);
}

char	*ft_itoa(int n)
{
	size_t	alloc_size;
	char	*alloc_memory;
	long	nc;

	nc = (long)n;
	alloc_size = ft_itoasize(nc);
	alloc_memory = malloc((alloc_size + 1) * sizeof(char));
	if (!alloc_memory)
		return (NULL);
	alloc_memory[alloc_size] = '\0';
	if (nc < 0)
	{
		alloc_memory[0] = '-';
		nc = -nc;
	}
	if (nc == 0)
		alloc_memory[0] = '0';
	while (nc)
	{
		alloc_memory[--alloc_size] = (nc % 10) + '0';
		nc /= 10;
	}
	return (alloc_memory);
}
