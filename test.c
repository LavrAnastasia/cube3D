#include "game.h"
#include "engine.h"
#include "libft.h"
// module engine

#define SIZE 10 // TODO: delete


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
    game.map_meta.height = SIZE;
    game.map_meta.width = SIZE;

    game.player_pos.x = 2.0;
    game.player_pos.y = 2.0;

    static char *mock_map[SIZE] = {
        "1111111111",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1000000001",
        "1111111111"
    };

    game.map = ft_calloc(game.map_meta.height + 1, sizeof(char *));
    if (!game.map)
        return (1); // TODO: error handling
    int i = 0;
    for (i = 0; i < game.map_meta.height; i++) {
        game.map[i] = ft_strdup(mock_map[i]);
        if (!game.map[i])
            return (1); // TODO: error handling + cleanup
    }   

    game.map[game.map_meta.height] = NULL;

    // TODO: Engine Header now knows about game, this is unappropriate
    engine_init(&game);

    return (0);
}