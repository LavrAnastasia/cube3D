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
#include "parsing_types.h"

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








char *map_key(t_direction_key key);

t_parse_result parse_settings(t_configuration *configuration, char **argv);
t_parse_result check_args(int argc, char **argv);
void print_error_msg(const char *msg);
t_parse_result process_config_line(char *line, t_configuration *configuration, t_config_state *st);
int parse_clean(int fd, char *line);

char *skip_spaces(char *s);
bool is_direction_key(const char *line, t_direction_key key);
int is_color_key(const char *line, const char a);

void free_str_array(char **arr);
void print_error_key(const char *key, const char *msg);
t_parse_result parse_color(char *raw, t_rgb *color);

void print_parse_error(t_parse_error error);
t_parse_result parse_texture_path(char *line, char **path, t_direction_key key);
t_parse_result is_texture_path_missing(t_configuration *configuration);

t_parse_result parse_map(int fd, t_configuration *configuration, char *first_map_line);
int	is_valid_map_rows(char **map);
bool 	is_one_player(char **map);
int row_len(char *s);
void free_map(char **map, int rows);
int is_map_closed(char **map, int rows, t_position position);
void find_player_start(char **map, t_configuration *configuration);
bool is_map_row(char *line);

#endif