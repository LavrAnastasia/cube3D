/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:03:01 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:24:33 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;

	ptr = malloc((n + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s, n);
	ptr[n] = '\0';
	return (ptr);
}

static void	ft_free_split(char **arr, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_split_fill(char **result, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	str_size;

	i = 0;
	j = 0;
	while (s[i])
	{
		str_size = 0;
		if (s[i] != c)
		{
			while (s[i + str_size] && s[i + str_size] != c)
				str_size++;
			result[j] = ft_strndup(s + i, str_size);
			if (!result[j])
				return (ft_free_split(result, j), NULL);
			j++;
			i += str_size;
		}
		else
			i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	return (ft_split_fill(result, s, c));
}
