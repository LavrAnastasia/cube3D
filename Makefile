NAME := cub3D

DIR_SRC := src/
DIR_MAPS := maps/
DIR_UTILS := utils/
DIR_INTERACTIONS := interactions/
DIR_GRAPHICS := graphics/
DIR_ERRORS := errors/

SRC_ENGINE := $(addprefix $(DIR_SRC)engine/, index.c)
SRC_GRAPHICS := $(addprefix $(DIR_SRC)graphics/, graphics_destroy.c \
	graphics_load.c)
SRC_RAYCAST:= $(addprefix $(DIR_SRC)raycast/, index.c )
SRC_RENDER := $(addprefix $(DIR_SRC)render/, index.c )
SRC_MATH := $(addprefix $(DIR_SRC)math/, index.c )

SRC_MANDATORY := index.c \
	src/parsing/read_cube.c \
	$(SRC_MATH) \
	$(SRC_ENGINE) \
	$(SRC_RENDER) \
	$(SRC_RAYCAST) \
	$(SRC_GRAPHICS)

OBJ := $(SRC_MANDATORY:.c=.o)

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
BASE_FLAGS := -Wall -Wextra -Werror -Imlx -Iinclude -Ilibft
DEBUG_FLAGS := -g
SANITAZE_FLAGS := -fsanitize=address

ifeq ($(MODE),debug)
	CFLAGS = $(BASE_FLAGS) $(DEBUG_FLAGS) $(SANITAZE_FLAGS)
else ifeq ($(MODE),valgrind)
	CFLAGS = $(BASE_FLAGS) $(DEBUG_FLAGS)
else
	CFLAGS = $(BASE_FLAGS)
endif

all: $(NAME)

%.o: %.c
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
	rm -f $(OBJ)
	$(MAKE) -C libft clean
	@if [ -d $(MLX_DIR) ]; then \
		$(MAKE) -C $(MLX_DIR) clean; \
	fi

fclean:
	$(MAKE) -C libft fclean
	rm -f $(OBJ) $(NAME)
	@if [ -d $(MLX_DIR) ]; then \
		rm -rf $(MLX_DIR); \
	fi
	

re: fclean all

debug:
	$(MAKE) MODE=debug

valgrind:
	$(MAKE) MODE=valgrind

.PHONY: all clean fclean re debug valgrind