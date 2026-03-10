#include "parsing.h"

int	main(int argc, char **argv)
{
    t_game	game;

	ft_bzero(&game, sizeof(t_game));

    // Init Game
    // Validate Input
    // Validate Maps
    // Parse Input & Init Game
    // Init Graphics
    // Render
    // Hooks
    // Mlx_loop

    if(check_args(argc, argv))
        return(1);
    if(parse_settings(&game, argv) != 0)
        return (1);
    return (0);
}