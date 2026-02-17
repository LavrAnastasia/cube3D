/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:01:45 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:24:59 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*alloc_memory;
	size_t	s1_len;
	size_t	s2_len;
	size_t	alloc_size;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	alloc_size = s1_len + s2_len + 1;
	alloc_memory = malloc(alloc_size * sizeof(char));
	if (!alloc_memory)
		return (NULL);
	ft_strlcpy(alloc_memory, s1, s1_len + 1);
	ft_strlcat(alloc_memory, s2, alloc_size);
	return (alloc_memory);
}
