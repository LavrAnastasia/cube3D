/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:56 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:25:39 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char			*ptr;
	unsigned char		converted_char;

	ptr = NULL;
	converted_char = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == converted_char)
			ptr = s;
		s++;
	}
	if (converted_char == '\0')
		return ((char *)(s));
	return ((char *)(ptr));
}
