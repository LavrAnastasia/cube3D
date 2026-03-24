#include "parsing_internal.h"

t_parse_result	make_parse_success_result(t_parse_type p_type)
{
	return ((t_parse_result){.ok = true, .parse_type = p_type});
}

t_parse_result make_parse_error_result(t_parse_error_code code, const char *info)
{
	return (t_parse_result) {
		.ok = false,
		.error = (t_parse_error) {
			.code = code,
			.info = info
		}
	};
}