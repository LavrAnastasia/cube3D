/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alavrukh <alavrukh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:28:02 by timlive           #+#    #+#             */
/*   Updated: 2026/03/24 14:42:14 by alavrukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parsing.h"
#include "parsing_internal.h"

t_parse_result	check_args(int argc, char **argv)
{
	char			*dot;
	t_parse_result	result;

	result.ok = true;
	if (argc < 2)
		return (make_parse_error_result(P_ERR_NO_INPUT_FILE, NULL));
	if (argc > 2)
		return (make_parse_error_result(P_ERR_ARG, NULL));
	dot = ft_strrchr(argv[1], '.');
	if (!dot || ft_strncmp(dot, FILE_EXT, 5) != 0)
		return (make_parse_error_result(P_ERR_EXTENSION, NULL));
	return (result);
}

t_parse_result	read_config_until_map(
	int fd,
	t_configuration *configuration,
	char **first_map_line,
	t_config_state *st)
{
	char			*line;
	t_parse_result	result;

	*first_map_line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (make_parse_error_result(P_ERR_EMPTY_FILE, NULL));
	while (line)
	{
		result = process_config_line(line, configuration, st);
		if (!result.ok)
		{
			free(line);
			return (result);
		}
		if (result.parse_type == P_MAP)
		{
			*first_map_line = line;
			return (result);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (result);
}

t_parse_result	parse_settings(t_configuration *configuration, char **argv)
{
	int				fd;
	char			*first_map_line;
	t_parse_result	result;
	t_config_state st;

	st.seen_floor = 0;
	st.seen_ceiling = 0;
	first_map_line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (make_parse_error_result(P_ERR_OPEN_FILE, NULL));
	result = read_config_until_map(fd, configuration, &first_map_line, &st);
	if (!result.ok)
	{
		if (first_map_line)
			free(first_map_line);
		close(fd);
		return (result);
	}
	result = is_texture_path_missing(configuration);
	if(!result.ok)
	{
		if (first_map_line)
			free(first_map_line);
		close(fd);
		return (result);
	}
	if (!first_map_line)
	{
		close(fd);
		return (make_parse_error_result(P_ERR_EMPTY_MAP, NULL));
	}
	if(!st.seen_floor || !st.seen_ceiling)
	{
		if (first_map_line)
			free(first_map_line);
		close(fd);
		return(make_parse_error_result(P_ERR_NOT_COLOR, NULL));
	}
    result = parse_map(fd, configuration, first_map_line);
	free(first_map_line);
	close(fd);
	return (result);
}
