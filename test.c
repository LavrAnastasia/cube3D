#include "game.h"
#include "engine.h"
#include "libft.h"
// module engine




int	main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    // Init Game
    // Validate Input
    // Validate Maps
    // Parse Input & Init Game
    // Init Graphics
    // Render
    // Hooks
    // Mlx_loop

    t_game	game;

	ft_bzero(&game, sizeof(t_game));

    
    // Mock info 
    game.map_meta.height = 10;
    game.map_meta.width = 10;

    game.player_pos.x = 2.0;
    game.player_pos.y = 2.0;

    engine_init(&game);

    return (0);
}