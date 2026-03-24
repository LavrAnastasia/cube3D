#ifndef PARSING_TYPES_H
#define PARSING_TYPES_H

typedef enum e_parse_error_code
{
	P_ERR_MALLOC,
	P_ERR_NO_INPUT_FILE,
	P_ERR_NO_PATH,
	P_ERR_ARG,
	P_ERR_EXTENSION,
	P_ERR_OPEN_FILE,
	P_ERR_RGB,
	P_ERR_RGB_RANGE, 
	P_ERR_DUP,
	P_ERR_TEXTURE_EXT,
	P_ERR_TEXTURE_TRAILING,
	P_ERR_INVALID_SYMBOLS,
	P_ERR_PLAYER_COUNT,
	P_ERR_MAP_NOT_CLOSED,
	P_ERR_DUP_FLOOR,
	P_ERR_DUP_CEILING,
	P_ERR_NOT_COLOR,
	P_ERR_INVALID_CONFIG_LINE,
	P_ERR_EMPTY_MAP,
	P_ERR_EMPTY_FILE,
	P_ERR_MAP_EMPTY_LINE,
	P_ERR_EMPTY_FILE_NAME

} t_parse_error_code;

typedef struct s_parse_error {
	t_parse_error_code code;
	const char *info;
} t_parse_error;

typedef enum e_parse_type
{
	P_NONE = 0,
	P_TEXTURE,
	P_COLOR,
	P_MAP
} t_parse_type;

typedef struct s_parse_result {
	bool ok;
	t_parse_type parse_type;
	t_parse_error error;
} t_parse_result;

#endif