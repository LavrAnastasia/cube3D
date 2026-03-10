#ifndef PARSING_H
#define PARSING_H

#include <fcntl.h> //open
#include <unistd.h> // close, read 
#include <stdio.h> // printf, perror
#include <stdlib.h> // free, malloc, exits
#include "libft.h"
#include "game.h"
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


int parse_settings(t_game *game, char **argv);
int check_args(int argc, char **argv);
int print_error_msg(char *msg);
int parse_config_section(char *line, t_game *game);
int parse_clean(int fd, char *line);

char *skip_spaces(char *s);
int is_direction_config(char *line, char a, char b);
int is_config(char *line, char a);

void free_split(char **arr);
int	print_error_key(const char *key, const char *msg);
int parse_texture(char *raw, char **saved, const char *key_name);
int parse_color(char *raw, t_rgb *color, const char *key_name);
int parse_before_map(char *line);


#endif