#include "parsing.h"
#include "game.h"
#include "libft.h"


#define SIZE 10 // TODO: delete

// GAME LEVEL

int	main(int argc, char **argv)
{
	t_game	game;
	t_parse_result parse_result;
	t_configuration configuration;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&configuration, sizeof(t_configuration));

	parse_result = check_args(argc, argv);
	if (!parse_result.ok)
	{
		print_parse_error(parse_result.error);
		return (1);
	}

	parse_result = parse_settings(&configuration, argv);
	if (!parse_result.ok)
	{
		print_parse_error(parse_result.error);
		return (1);
	}

	printf("Parse type: %d", parse_result.parse_type);


	// INIT_SCENE	
	// TODO: clean Map
	if (!game_init_scene(&game.scene, &configuration))
		game_shutdown(&game, EXIT_FAILURE);


	// INIT ENGINE
	if (!game_init_engine(&game))
		game_shutdown(&game, EXIT_FAILURE);

	// LOAD TEXTURES
	// TODO: clean CONFIG PATHES
	if (!game_init_textures(&game.textures, &configuration, game.engine.mlx_session))
		game_shutdown(&game, EXIT_FAILURE);

	//RUN LOOP	

	engine_run(&game.engine);

	return (0);
}