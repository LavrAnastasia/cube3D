#ifndef PARSING_H
#define PARSING_H

#include "config.h"
#include "parsing_types.h"

void destroy_parsing_config(t_configuration *configuration);
t_parse_result parse_settings(t_configuration *configuration, char **argv);
void print_parse_error(t_parse_error error);

#endif