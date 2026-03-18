/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_settings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timlive <timlive@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:28:02 by timlive           #+#    #+#             */
/*   Updated: 2026/03/18 12:55:18 by timlive          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "parsing.h"

static t_parse_result	make_parse_error_result(t_parse_error_code code)
{
	return ((t_parse_result){.ok = false, .error = (t_parse_error){.code = code,
		.info = NULL}});
}

t_parse_result	check_args(int argc, char **argv)
{
	char			*dot;
	t_parse_result	result;

	result.ok = true;
	if (argc < 2)
		return (make_parse_error_result(P_ERR_NO_MAP));
	if (argc > 2)
		return (make_parse_error_result(P_ERR_ARG));
	dot = ft_strrchr(argv[1], '.');
	if (!dot || ft_strncmp(dot, FILE_EXT, 5) != 0)
		return (make_parse_error_result(P_ERR_EXTENSION));
	return (result);
}

t_parse_result	read_config_until_map(
	int fd,
	t_configuration *configuration,
	char **first_map_line)
{
	char			*line;
	t_parse_result	result;
	t_parse_type type;

	*first_map_line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (make_parse_error_result(P_ERR_NO_MAP));
	while (line)
	{
		result = process_config_line(line, configuration, &type);
		if (!result.ok)
		{
			free(line);
			return (result);
		}
		if (type == P_MAP)
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

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (make_parse_error_result(P_ERR_OPEN_FILE));
	result = read_config_until_map(fd, configuration, &first_map_line);
	if (!result.ok)
	{
		close(fd);
		return (result);
	}
	if (is_texture_path_missing(configuration))
	{
		close(fd);
		return (make_parse_error_result(P_ERR_NO_PATH));
	}
	if (!first_map_line)
	{
		close(fd);
		return (make_parse_error_result(P_ERR_NO_MAP));
	}

    result = parse_map(fd, configuration, first_map_line);

	free(first_map_line);
	close(fd);
	return (result);
}
