#include "parsing.h"

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

    if(argc != 2)
        return(printf("Please provide a .cub map file"), 1);
    return(read_cube(argv[1]));
}