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












void destroy_parsing_config(t_configuration *configuration);



char *map_key(t_direction_key key);

t_parse_result parse_settings(t_configuration *configuration, char **argv);
t_parse_result check_args(int argc, char **argv);
void print_error_msg(const char *msg);
t_parse_result process_config_line(char *line, t_configuration *configuration, t_config_state *st);





void print_error_key(const char *key, const char *msg);
t_parse_result parse_color_line(char *raw, t_rgb *color);

void print_parse_error(t_parse_error error);

t_parse_result is_texture_path_missing(t_configuration *configuration);

t_parse_result parse_map(int fd, t_configuration *configuration, char *first_map_line);
int	is_valid_map_rows(char **map);
bool 	validate_payer_pos(char **map, t_configuration *configuration);

t_parse_result is_map_closed(char **map, int rows, t_position position);


#endif