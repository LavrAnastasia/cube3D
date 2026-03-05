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
# define MANY_ARG "Too many arguments provided, required: program + map"
# define EXTENTION_MSG "Map must have .cub extension"
# define OPEN_FILE "Cannot open the file"

int parse_settings(t_game *game, char **argv);
int check_args(int argc, char **argv);
int print_error_msg(char *msg);
void init_config(t_config *config);
int parse_config_section(char *line, t_game *game);
int parse_clean(int fd, char *line);


#endif