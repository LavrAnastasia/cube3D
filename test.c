#include "game.h"
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
    // INIT ENGINE
    game.engine.window_width  = MAX_WIN_WIDTH;
    game.engine.window_height = MAX_WIN_HEIGHT;
    if (!engine_init(&game.engine, GAME_TITLE)) {
        // TODO: clean other sources
        return (1);
    }

    // INIT GRAPHICS
    game.graphics.tile_size = TILE_SIZE; 
    if (!graphics_load(&game.graphics, game.engine.mlx_session)) {
        // TODO: clean other sources
        graphics_destroy(&game.graphics, game.engine.mlx_session);
        engine_shutdown(&game.engine);
        return (1);
    }

    return (0);
}