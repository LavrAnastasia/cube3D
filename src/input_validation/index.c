#include "libft.h"
#include "validation_types.h"
#include "parsing_settings.h"


static t_validation_result	make_input_success_result(void);
static t_validation_result	make_input_error_result(t_validation_error_code code);

t_validation_result	check_args(int argc, char **argv)
{
	char			*dot;
	char *filename;
	char *slash;

	if (argc < 2)
		return (make_input_error_result(V_ERR_NO_INPUT_FILE));
	if (argc > 2)
		return (make_input_error_result(V_ERR_ARG));
	slash = ft_strrchr(argv[1], '/');
	if(slash != NULL)
		filename = slash + 1;
	else 
		filename = argv[1];
	if(ft_strcmp(filename, FILE_EXT) == 0)
		return (make_input_error_result(V_ERR_EMPTY_FILE_NAME));
	dot = ft_strrchr(argv[1], '.');
	if (!dot || ft_strcmp(dot, FILE_EXT) != 0)
		return (make_input_error_result(V_ERR_EXTENSION));
	return (make_input_success_result());
}

static t_validation_result	make_input_success_result(void)
{
	return ((t_validation_result){.ok = true});
}

static t_validation_result make_input_error_result(t_validation_error_code code)
{
	return (t_validation_result) {
		.ok = false,
		.error_code = code
	};
}