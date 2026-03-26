#ifndef VALIDATION_TYPES_H
#define VALIDATION_TYPES_H

#include <stdbool.h>

#include "validation_errors.h"

typedef struct s_validation_result {
	bool ok;
	t_validation_error_code error_code;
} t_validation_result;


#endif