#include "parsing.h"
#include "game.h"
#include "libft.h"


#define SIZE 10 // TODO: delete

// GAME LEVEL

int	main(int argc, char **argv)
{
	t_game	game;
	t_parse_result parse_result;

	ft_bzero(&game, sizeof(t_game));

	parse_result = check_args(argc, argv);
	if (!parse_result.ok)
	{
		print_parse_error(parse_result.error);
		return (1);
	}
	parse_result = parse_settings(&game, argv);
	if (!parse_result.ok)
	{
		print_parse_error(parse_result.error);
		return (1);
	}

	static char *mock_map[SIZE] = {
		"1111111111",
		"1000000001",
		"1000000001",
		"1000010001",
		"1000010001",
		"1000010001",
		"1000010001",
		"1000000001",
		"1000000001",
		"1111111111"
	};

	// INIT_SCENE	
	if (!game_init_scene(&game.scene, &game.config, mock_map, (t_dimensions){.height = SIZE, .width = SIZE}))
		game_shutdown(&game, EXIT_FAILURE);

	// INIT ENGINE
	if (!game_init_engine(&game))
		game_shutdown(&game, EXIT_FAILURE);

	// LOAD TEXTURES
	if (!game_init_textures(&game.textures, &game.config, game.engine.mlx_session))
		game_shutdown(&game, EXIT_FAILURE);
	engine_run(&game.engine);

	return (0);
}