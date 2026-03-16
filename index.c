#include "parsing.h"
#include "game.h"
#include "libft.h"


#define SIZE 10 // TODO: delete


// DEBUG

void debug_print(t_game *game)
{
	char *str = game->config.ea_path;
	char *fake_str =  "resources/ea.xpm";

	

	if (ft_strcmp(str, fake_str) == 0)
		printf("WE ARE EQ \n");
	else 
		printf("WE ARE NOT EQ \n");
	
	printf("STRING:%s_END\n", str);
	printf("STRING:%s_END\n", fake_str);
}

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

	// TODO: check spaces after teh path 
	// TODO: check what wrong with textures
	debug_print(&game);
	const t_wall_texture_paths paths = (t_wall_texture_paths) {
		.east =  "resources/ea.xpm",
        .north = "resources/no.xpm",
        .south = "resources/so.xpm", 
        .west = "resources/we.xpm"
	};

	if (textures_load(&game.textures, game.engine.mlx_session, &paths) != TEX_OK) {
		engine_shutdown(&game.engine);
		return (1);
	}
	engine_run(&game.engine);

	return (0);
}