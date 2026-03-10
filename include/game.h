#ifndef GAME_H
# define GAME_H

# include "config.h"
# include "engine.h"
# include "textures.h"
# include "scene.h"
# include "controls_state.h"

# define FOV 60
# define GAME_TITLE "CUB3D"

# ifdef __linux__
#  define MAX_WIN_WIDTH 2560
#  define MAX_WIN_HEIGHT 1440
# else
#  define MAX_WIN_WIDTH 1920
#  define MAX_WIN_HEIGHT 1080
# endif

typedef struct s_game
{
	t_engine			engine;
	t_textures			textures;
	t_scene				scene;
	t_config			config;
	t_controls_state 	controls_state;
}				t_game;

#endif