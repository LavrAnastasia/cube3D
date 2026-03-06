#ifndef GAME_H
# define GAME_H

# include "engine.h"
# include "graphics.h"
# include "scene.h"

# define FOV 60
# define GAME_TITLE  "CUB3D"

# ifdef __linux__
#  define MAX_WIN_WIDTH 2560
#  define MAX_WIN_HEIGHT 1440
# else
#  define MAX_WIN_WIDTH 1920
#  define MAX_WIN_HEIGHT 1080
# endif

typedef struct s_game
{
	t_engine		engine;
	t_textures		textures;
	t_scene			scene;
}	t_game;

#endif