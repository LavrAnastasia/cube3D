/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 15:40:06 by alavrukh          #+#    #+#             */
/*   Updated: 2026/03/27 15:44:23 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

char	*skip_spaces(char *s)
{
	if (!s)
		return (NULL);
	while (ft_isspace(*s))
		s++;
	return (s);
}

void	cleanup_parse_resource(int fd, char *line)
{
	if (line)
		free(line);
	close(fd);
}

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

bool	is_xpm_extension(const char *value)
{
	char	*dot;

	if (!value)
		return (false);
	dot = ft_strrchr(value, '.');
	if (!dot)
		return (false);
	if (ft_strcmp(dot, IMG_EXT) != 0)
		return (false);
	return (true);
}
