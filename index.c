#include "game.h"
#include "parsing.h"
#include "reporter.h"
#include "validation.h"
#include <stdlib.h>

static bool	config_validation(int argc, char **argv,
				t_configuration *configuration);

int	main(int argc, char **argv)
{
	t_game			game;
	t_configuration	configuration;

	game = (t_game){0};
	configuration = (t_configuration){0};
	if (!config_validation(argc, argv, &configuration))
		return (EXIT_FAILURE);
	if (!game_init(&game, &configuration))
	{
		destroy_parsing_config(&configuration);
		game_shutdown(&game, EXIT_FAILURE);
	}
	destroy_parsing_config(&configuration);
	engine_run(&game.engine);
	return (0);
}

static bool	config_validation(int argc, char **argv,
		t_configuration *configuration)
{
	t_parse_result		parse_result;
	t_validation_result	validation_result;

	validation_result = check_args(argc, argv);
	if (!validation_result.ok)
	{
		report(D_VALIDATION, validation_result.error_code, SL_ERROR);
		return (false);
	}
	parse_result = parse_settings(configuration, argv);
	if (!parse_result.ok)
	{
		destroy_parsing_config(configuration);
		print_parse_error(parse_result.error);
		return (false);
	}
	return (true);
}
