#include "parsing_internal.h"

void destroy_parsing_config(t_configuration *configuration)
{
	if (!configuration)
		return;
	if (configuration->map)
	{
		free_str_array(configuration->map);
		configuration->map = NULL;
	}
	if (configuration->samples.paths.east)
		free(configuration->samples.paths.east);
	if (configuration->samples.paths.north)
		free(configuration->samples.paths.north);
	if (configuration->samples.paths.south)
		free(configuration->samples.paths.south);
	if (configuration->samples.paths.west)
		free(configuration->samples.paths.west);
}

t_parse_result	check_args(int argc, char **argv)
{
	char			*dot;
	t_parse_result	result;

	if (argc < 2)
		return (make_parse_error_result(P_ERR_NO_INPUT_FILE, NULL));
	if (argc > 2)
		return (make_parse_error_result(P_ERR_ARG, NULL));
	if (ft_strcmp(argv[1], FILE_EXT) == 0) 
		return (make_parse_error_result(P_ERR_EMPTY_FILE_NAME, NULL));
	dot = ft_strrchr(argv[1], '.');
	if (!dot || ft_strcmp(dot, FILE_EXT) != 0)
		return (make_parse_error_result(P_ERR_EXTENSION, NULL));
	result.ok = true;
	return (result);
}

t_parse_result	parse_settings(t_configuration *configuration, char **argv)
{
	int				fd;
	char			*first_map_line;
	t_parse_result	result;
	t_config_state state;

	state = (t_config_state){0};
	first_map_line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (make_parse_error_result(P_ERR_OPEN_FILE, NULL));
	result = read_config_until_map(fd, configuration, &first_map_line, &state);
	if (!result.ok)
	{
		cleanup_parse_resource(fd, first_map_line);
		return (result);
	}
	result = is_texture_path_missing(configuration);
	if(!result.ok)
	{
		cleanup_parse_resource(fd, first_map_line);
		return (result);
	}
	if (!first_map_line)
	{
		cleanup_parse_resource(fd, first_map_line);
		return (make_parse_error_result(P_ERR_EMPTY_MAP, NULL));
	}
	if(!state.seen_floor || !state.seen_ceiling)
	{
		cleanup_parse_resource(fd, first_map_line);
		return(make_parse_error_result(P_ERR_NOT_COLOR, NULL));
	}
    result = parse_map(fd, configuration, first_map_line);
	cleanup_parse_resource(fd, first_map_line);
	return (result);
}

void print_parse_error(t_parse_error error)
{   
	if (error.info != NULL)
		print_error_key(error.info, err_parse_msg(error.code));
	else
		print_error_msg(err_parse_msg(error.code));
}