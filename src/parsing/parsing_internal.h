#ifndef PARSING_INTERNAL_H
#define PARSING_INTERNAL_H

#include <stdbool.h>

#include "parsing_types.h"

t_parse_result	make_parse_success_result(t_parse_type p_type);
t_parse_result	make_parse_error_result(t_parse_error_code code, const char *info);

#endif