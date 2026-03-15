#ifndef PARSING_H
#define PARSING_H

#include <fcntl.h> //open
#include <unistd.h> // close, read 
#include <stdio.h> // printf, perror
#include <stdlib.h> // free, malloc, exits
#include <stdbool.h>

#include "libft.h"
#include "game.h" // TODO: delete
#include "config.h"

//error messages

#define SKIP_SIGN ' '

#define NO_KEY "NO"
#define SO_KEY "SO"
#define WE_KEY "WE"
#define EA_KEY "EA"

typedef enum e_direction_key
{
	NO = 0,
	SO,
	WE,
	EA
}	t_direction_key;

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
	P_ERR_NO_MAP,
	P_ERR_NO_PATH,
	P_ERR_ARG,
	P_ERR_EXTENSION,
	P_ERR_OPEN_FILE,
	P_ERR_RGB,
	P_ERR_RGB_RANGE, 
	P_ERR_DUP,
	P_ERR_TEXTURE_EXT,
	P_ERR_TEXTURE_TRAILING

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

t_parse_result parse_settings(t_game *game, char **argv);
t_parse_result check_args(int argc, char **argv);
void print_error_msg(const char *msg);
t_parse_result process_config_line(char *line, t_game *game);
int parse_clean(int fd, char *line);

char *skip_spaces(char *s);
bool is_direction_key(const char *line, t_direction_key key);
int is_config(const char *line, const char a);

void free_split(char **arr);
void print_error_key(const char *key, const char *msg);
t_parse_result parse_color(char *raw, t_rgb *color, const char *key_name);
bool is_next_line_map(char *line);

void print_parse_error(t_parse_error error);
t_parse_result fill_texture_path(char *line, char **path, t_direction_key key);
int is_texture_path_missing(t_game *game);


#endif