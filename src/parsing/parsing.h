#ifndef PARSING_H
#define PARSING_H


#include <unistd.h> // close, read 
#include <stdio.h> // printf, perror
#include <stdlib.h> // free, malloc, exits
#include <stdbool.h>

#include "libft.h"
#include "config.h"
#include "map.h"
#include "parsing_types.h"

//error messages














void destroy_parsing_config(t_configuration *configuration);



char *map_key(t_direction_key key);

t_parse_result parse_settings(t_configuration *configuration, char **argv);
t_parse_result check_args(int argc, char **argv);
void print_error_msg(const char *msg);






void print_error_key(const char *key, const char *msg);
t_parse_result parse_color_line(char *raw, t_rgb *color);

void print_parse_error(t_parse_error error);









#endif