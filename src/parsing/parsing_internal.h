#ifndef PARSING_INTERNAL_H
#define PARSING_INTERNAL_H

#include <stdbool.h>
#include <stdlib.h>

#include "libft.h"
#include "parsing_types.h"
#include "parsing_settings.h"
#include "config.h"

t_parse_result	make_parse_success_result(t_parse_type p_type);
t_parse_result	make_parse_error_result(t_parse_error_code code, const char *info);

void cleanup_parse_resource(int fd, char *line);
void free_str_array(char **arr);
bool is_map_row(char *line);
int row_len(char *s);
t_parse_result parse_texture_line(char *line, char **path, t_direction_key key);
char *skip_spaces(char *s);
bool is_color_key(const char *line, const char a);
bool is_direction_key(const char *line, t_direction_key key);
t_parse_result is_map_closed(char **map, int rows, t_position position);
int	is_valid_map_rows(char **map);
bool 	validate_payer_pos(char **map, t_configuration *configuration);


#endif