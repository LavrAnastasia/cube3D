#include "parsing.h"
#include "parsing_internal.h"
#include "map_utils.h"

bool is_map_row(char *line)
{
	int i;
	int has_map_char;
	

	if(!line || !*line)
		return(false);
	i = 0;
	has_map_char = 0;
	while(line[i] && line[i] != '\n')
	{
		if(!is_valid_char(line[i]) && (line[i] != SKIP_SIGN))
			return(false);
		if(line[i] != SKIP_SIGN)
			has_map_char = true;
		i++;
	}
	return (has_map_char);
}

char *map_key(t_direction_key key)
{
	if (key == NO)
		return NO_KEY;
	if (key == SO)
		return SO_KEY;
	if (key == WE)
		return WE_KEY;
	return EA_KEY;  
}

bool is_direction_key(const char *line, t_direction_key key)
{
	const char *direction_key = map_key(key);

	if(!line || !line[0] || !line[1] || !line[2])
		return false;
	if(line[0] != direction_key[0])
		return(false);
	if(line[1] != direction_key[1])
		return (false);
	if(!ft_isspace((unsigned char)line[2]))
		return (false);
	return (true);
}
int is_color_key(const char *line, const char a)
{
	if(!line || !line[0] || !line[1])
		return(0);
	if(line[0] != a)
		return(0);
	if(!ft_isspace((unsigned char)line[1]))
		return(0);
	return(1);    
}

t_parse_result is_texture_path_missing(t_configuration *configuration)
{
	const int err_code = P_ERR_NO_PATH;
	
	if (!configuration->samples.paths.north)
		return(make_parse_error_result(err_code ,NO_KEY));
	if (!configuration->samples.paths.south)
		return(make_parse_error_result(err_code ,SO_KEY));
	if (!configuration->samples.paths.west)
		return(make_parse_error_result(err_code ,WE_KEY));
	if (!configuration->samples.paths.east)
		return(make_parse_error_result(err_code ,EA_KEY));
	return (make_parse_success_result(P_NONE));
}

