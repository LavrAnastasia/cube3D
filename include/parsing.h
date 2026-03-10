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
# define NO_MAP "Please provide a .cub map file"
# define ERR_MAP "Map section is missing"
# define MANY_ARG "Too many arguments provided, required: program + map"
# define EXTENTION_MSG "Map must have .cub extension"
# define OPEN_FILE "Cannot open the file"

#define NO_PATH "Texture path is missing"
#define DUP "Duplicate texture key"
#define ERR_MALLOC "Malloc failed"
#define ERR_RGB "Invalid RGB format"
#define ERR_RGB_RANGE "RGB out of range"

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


char *map_key(t_direction_key key);

int parse_settings(t_game *game, char **argv);
int check_args(int argc, char **argv);
int print_error_msg(char *msg);
int parse_config_section(char *line, t_game *game);
int parse_clean(int fd, char *line);

char *skip_spaces(char *s);
bool is_direction_key(char *line, t_direction_key key);
int is_config(char *line, char a);

void free_split(char **arr);
int	print_error_key(const char *key, const char *msg);
int parse_color(char *raw, t_rgb *color, const char *key_name);
bool is_next_line_map(char *line);


#endif