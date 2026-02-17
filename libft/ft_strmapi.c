/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:55:19 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/24 17:24:34 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			str_len;
	unsigned int	i;
	char			*alloc_memory;

	if (!s || !f)
		return (NULL);
	str_len = ft_strlen(s);
	alloc_memory = malloc((str_len + 1) * sizeof(char));
	if (!alloc_memory)
		return (NULL);
	i = 0;
	while (s[i])
	{
		alloc_memory[i] = f(i, s[i]);
		i++;
	}
	alloc_memory[i] = '\0';
	return (alloc_memory);
}
