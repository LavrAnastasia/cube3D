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