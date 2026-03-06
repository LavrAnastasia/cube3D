#include "game.h"
#include "libft.h"
#include "render.h"
// module engine
#include "math_u.h" // TODO: prbl delete in future
#include <mlx.h>

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
    game.scene.map_size.height = SIZE;
    game.scene.map_size.width = SIZE;

    game.scene.player.pos.x = 2.0;
    game.scene.player.pos.y = 2.0;

    game.scene.player.angle = 0.0;

    game.scene.palette.ceiling = 0x202030;
    game.scene.palette.floor = 0x151515;

    game.scene.map = ft_calloc(game.scene.map_size.height + 1, sizeof(char *));
    if (!game.scene.map)
        return (1); // TODO: error handling
    int i = 0;
    for (i = 0; i < game.scene.map_size.height; i++) {
        game.scene.map[i] = ft_strdup(mock_map[i]);
        if (!game.scene.map[i])
            return (1); // TODO: error handling + cleanup
    }   

    game.scene.map[game.scene.map_size.height] = NULL;

    game.scene.camera.fov = deg_to_rad(FOV);
    game.scene.camera.scale = tan(game.scene.camera.fov / 2);

    // INIT ENGINE
    game.engine.window_size = (t_dimensions){
        .width = MAX_WIN_WIDTH,
        .height = MAX_WIN_HEIGHT
    };
    if (!engine_init(&game.engine, GAME_TITLE)) {
        // TODO: clean other sources
        return (1);
    }

    // LOAD TEXTURES
    t_wall_texture_paths paths = (t_wall_texture_paths) {
        .east =  "resources/ea.xpm",
        .north = "resources/no.xpm",
        .south = "resources/so.xpm", 
        .west = "resources/we.xpm"
    };

    if (!textures_load(&game.textures, game.engine.mlx_session, &paths)) {
        engine_shutdown(&game.engine);
        return (1);
    }
    render(&game.scene, game.engine.window_size, &game.engine.buffer.px, &game.textures);
    mlx_put_image_to_window(game.engine.mlx_session,
                        game.engine.mlx_window,
                        game.engine.buffer.img,
                        0, 0);
    engine_run(&game.engine);

    return (0);
}