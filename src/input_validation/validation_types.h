#ifndef VALIDATION_TYPES_H
# define VALIDATION_TYPES_H

# include "validation_errors.h"
# include <stdbool.h>

typedef struct s_validation_result
{
	bool					ok;
	t_validation_error_code	error_code;
}							t_validation_result;

#endif