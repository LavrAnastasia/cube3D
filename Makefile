NAME := cub3D

DIR_SRC := src/

SRC_ENGINE := $(addprefix $(DIR_SRC)engine/, index.c \
	engine_hooks.c engine_mlx.c)
SRC_PIXELS := $(addprefix $(DIR_SRC)pixels/, index.c)
SRC_TEXTURES := $(addprefix $(DIR_SRC)textures/, index.c \
	textures_load.c textures_destroy.c)
SRC_RAYCAST:= $(addprefix $(DIR_SRC)raycast/, index.c \
	raycast_prepare_dda.c raycast_prepare_ray.c raycast_intersection.c)
SRC_RENDER := $(addprefix $(DIR_SRC)render/, index.c \
	render_draw.c render_projection.c render_sampling.c render_utils.c)
SRC_MATH := $(addprefix $(DIR_SRC)math/, index.c )

SRC_MOVEMENT := $(addprefix $(DIR_SRC)movement/, index.c \
	movement_time.c movement_position.c movement_rotation.c)

SRC_PARSING := $(addprefix $(DIR_SRC)parsing/, parse_settings.c \
	parse_config.c check_config.c parsing_utils.c parse_textures.c \
	parse_map.c validate_map.c parsing_result.c index.c)

SRC_MAP_UTILS := $(addprefix $(DIR_SRC)map/, index.c )

SRC_REPORTER := $(addprefix $(DIR_SRC)reporter/, index.c \
	reporter_warning.c)

SRC_GAME := $(addprefix game/, game_init_scene.c \
	game_init.c game_init_engine.c game_shutdown.c game_init_textures.c)

SRC_MANDATORY := index.c \
	$(SRC_GAME) \
	$(SRC_PARSING) \
	$(SRC_MATH) \
	$(SRC_ENGINE) \
	$(SRC_PIXELS) \
	$(SRC_RENDER) \
	$(SRC_RAYCAST) \
	$(SRC_TEXTURES) \
	$(SRC_MOVEMENT) \
	$(SRC_MAP_UTILS) \
	$(SRC_REPORTER)

OBJ_DIR := obj

OBJ := $(addprefix $(OBJ_DIR)/, $(SRC_MANDATORY:.c=.o))

LIBFLAGS := -L./libft -lft
LIBFT := libft/libft.a

UNAME_S := $(shell uname -s)

MLX_DIR := mlx
MLX_LIB := $(MLX_DIR)/libmlx.a

ifeq ($(UNAME_S),Linux)
	MLX_URL = https://cdn.intra.42.fr/document/document/43084/minilibx-linux.tgz
	MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
else
	MLX_URL = https://cdn.intra.42.fr/document/document/43085/minilibx_macos_opengl.tgz
	MLX_FLAGS = -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -framework Metal -framework QuartzCore
endif

CC := cc
BASE_FLAGS := -Wall -Wextra -Werror -Imlx -Iinclude -Ilibft \
	-Isrc/textures -Isrc/pixels -Isrc/raycast -Isrc/render -Isrc/engine -Isrc/math -Isrc/movement -Isrc/map \
	-Isrc/reporter -Isrc/parsing -Igame
DEBUG_FLAGS := -g
SANITIZE_FLAGS := -fsanitize=address

ifeq ($(MODE),debug)
	CFLAGS = $(BASE_FLAGS) $(DEBUG_FLAGS) $(SANITIZE_FLAGS)
else ifeq ($(MODE),valgrind)
	CFLAGS = $(BASE_FLAGS) $(DEBUG_FLAGS)
else
	CFLAGS = $(BASE_FLAGS)
endif

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS) $(MLX_FLAGS)

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Downloading MiniLibX..."; \
		curl -L $(MLX_URL) -o mlx.tgz; \
		tar -xzf mlx.tgz; \
		mv minilibx* $(MLX_DIR); \
		rm -f mlx.tgz; \
	fi
	$(MAKE) -C $(MLX_DIR)
$(LIBFT):
	$(MAKE) -C libft

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean
	@if [ -d $(MLX_DIR) ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft fclean
	rm -f $(NAME)
	@if [ -d $(MLX_DIR) ]; then \
		rm -rf $(MLX_DIR); \
	fi
	

re: fclean all

debug:
	$(MAKE) MODE=debug

valgrind:
	$(MAKE) MODE=valgrind

.PHONY: all clean fclean re debug valgrind