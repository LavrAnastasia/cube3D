/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:02 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/25 20:12:03 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_calloc_internal(size_t alloc_size)
{
	void	*alloc_memory;

	alloc_memory = malloc(alloc_size);
	if (!alloc_memory)
		return (NULL);
	ft_memset(alloc_memory, 0, alloc_size);
	return (alloc_memory);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	alloc_size;

	if (nmemb == 0 || size == 0)
		return (ft_calloc_internal(1));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	alloc_size = nmemb * size;
	return (ft_calloc_internal(alloc_size));
}
