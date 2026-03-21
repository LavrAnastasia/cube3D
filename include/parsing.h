#ifndef PARSING_H
#define PARSING_H

#include <fcntl.h> //open
#include <unistd.h> // close, read 
#include <stdio.h> // printf, perror
#include <stdlib.h> // free, malloc, exits
#include <stdbool.h>

#include "libft.h"
#include "config.h"
#include "map.h"

//error messages

#define FILE_EXT ".cub"
#define IMG_EXT ".xpm"

#define SKIP_SIGN ' '
#define VISITED_SIGN '*'

#define NO_KEY "NO"
#define SO_KEY "SO"
#define WE_KEY "WE"
#define EA_KEY "EA"
#define FLOOR_KEY "F"
#define CEILING_KEY "C"

typedef enum e_direction_key
{
	NO = 0,
	SO,
	WE,
	EA
}	t_direction_key;

typedef enum e_color_key
{
	C_FLOOR = 'F',
	C_CEILING = 'C'
}	t_color_key;

typedef enum e_parse_type
{
	P_UNKNOWN = 0,
	P_SPACES,
	P_TEXTURE,
	P_COLOR,
	P_MAP
} t_parse_type;

typedef enum e_parse_error_code
{
	P_ERR_MALLOC,
	P_ERR_NO_INPUT_FILE,
	P_ERR_NO_PATH,
	P_ERR_ARG,
	P_ERR_EXTENSION,
	P_ERR_OPEN_FILE,
	P_ERR_RGB,
	P_ERR_RGB_RANGE, 
	P_ERR_DUP,
	P_ERR_TEXTURE_EXT,
	P_ERR_TEXTURE_TRAILING,
	P_ERR_INVALID_SYMBOLS,
	P_ERR_PLAYER_COUNT,
	P_ERR_MAP_NOT_CLOSED,
	P_ERR_DUP_FLOOR,
	P_ERR_DUP_CEILING,
	P_ERR_NOT_COLOR,
	P_ERR_INVALID_CONFIG_LINE,
	P_ERR_EMPTY_MAP,
	P_ERR_EMPTY_FILE,
	P_ERR_MAP_EMPTY_LINE

} t_parse_error_code;

typedef struct s_parse_error {
	t_parse_error_code code;
	const char *info;
} t_parse_error;

typedef struct s_parse_result {
	bool ok;
	t_parse_type parse_type;
	t_parse_error error;
} t_parse_result;

char *map_key(t_direction_key key);

t_parse_result parse_settings(t_configuration *configuration, char **argv);
t_parse_result check_args(int argc, char **argv);
void print_error_msg(const char *msg);
t_parse_result process_config_line(char *line, t_configuration *configuration);
int parse_clean(int fd, char *line);

char *skip_spaces(char *s);
bool is_direction_key(const char *line, t_direction_key key);
int is_config(const char *line, const char a);

void free_split(char **arr);
void print_error_key(const char *key, const char *msg);
t_parse_result parse_color(char *raw, t_rgb *color);

void print_parse_error(t_parse_error error);
t_parse_result fill_texture_path(char *line, char **path, t_direction_key key);
int is_texture_path_missing(t_configuration *configuration);

t_parse_result parse_map(int fd, t_configuration *configuration, char *first_map_line);
int	is_valid_map_char(char **map);
bool 	is_one_player(char **map);
int row_len(char *s);
void free_map(char **map, int rows);
int check_path(char **map, int rows, t_position position);
void find_player_start(char **map, t_configuration *configuration);
bool is_map_row(char *line);

#endif