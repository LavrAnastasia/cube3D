#include "game.h"
#include "libft.h"
// module engine
#include "math_u.h" // TODO: prbl delete in future

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
    // Mock info
    game.scene.map_meta.height = SIZE;
    game.scene.map_meta.width = SIZE;

    game.scene.player.pos.x = 2.0;
    game.scene.player.pos.y = 2.0;

    game.scene.player.angle = 0.0;

    game.scene.map = ft_calloc(game.scene.map_meta.height + 1, sizeof(char *));
    if (!game.scene.map)
        return (1); // TODO: error handling
    int i = 0;
    for (i = 0; i < game.scene.map_meta.height; i++) {
        game.scene.map[i] = ft_strdup(mock_map[i]);
        if (!game.scene.map[i])
            return (1); // TODO: error handling + cleanup
    }   

    game.scene.map[game.scene.map_meta.height] = NULL;

    game.scene.camera.fov = deg_to_rad(FOV);

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

    engine_run(&game.engine);

    return (0);
}