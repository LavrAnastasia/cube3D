#include "parsing_internal.h"



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


