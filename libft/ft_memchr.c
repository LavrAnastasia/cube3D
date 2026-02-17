/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:22 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:23:32 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		character;

	ptr = (const unsigned char *)s;
	character = (unsigned char)c;
	while (n--)
	{
		if (*ptr == character)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
