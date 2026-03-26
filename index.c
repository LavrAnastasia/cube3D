#include <stdlib.h>
#include "parsing.h"
#include "game.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_parse_result parse_result;
	t_configuration configuration;

	game = (t_game){0};
	configuration = (t_configuration){0};
	parse_result = check_args(argc, argv);
	if (!parse_result.ok)
	{
		print_parse_error(parse_result.error);
		return (EXIT_FAILURE);
	}
	parse_result = parse_settings(&configuration, argv);
	if (!parse_result.ok)
	{
		destroy_parsing_config(&configuration);
		print_parse_error(parse_result.error);
		return (EXIT_FAILURE);
	}
	if (!game_init(&game, &configuration))
	{
		destroy_parsing_config(&configuration);
		game_shutdown(&game, EXIT_FAILURE);
	}
	destroy_parsing_config(&configuration);
	engine_run(&game.engine);
	return (0);
}
