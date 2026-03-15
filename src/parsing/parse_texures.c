#include "parsing.h"
static t_parse_result make_parse_error_result(t_parse_error_code code, const char *info)
{
    return (t_parse_result) {
        .ok = false,
        .error = (t_parse_error) {
            .code = code,
            .info = info
        }
    };
}
static t_parse_result make_parse_succses_result()
{
    return (t_parse_result) {
        .ok = true
    };
}

bool xpm_extention(const char *value)
{
    char *dot;

    if(!value)
        return(false);
    dot = ft_strrchr(value, '.');
    if(!dot)
        return(false);
    if(ft_strncmp(dot, ".xpm", 5) != 0)
        return(false);
    return(true);
}

static t_parse_result validate_texture_token(char *value, t_direction_key key)
{
    if(!xpm_extention(value))
        return (make_parse_error_result(P_ERR_TEXTURE_EXT, map_key(key)));
    return (make_parse_succses_result());
}

static char *get_texture_value_start(char *line, t_direction_key key, t_parse_result *res)
{
    char *start;

    start = skip_spaces(line);
    if(!start || *start == '\0' || *start == '\n')
    {
        *res = make_parse_error_result(P_ERR_NO_PATH, map_key(key));
        return (NULL);
    }
    *res = make_parse_succses_result();
    return(start);
}
static char *extract_texture_token(char *start, char **end_out, t_parse_result *res)
{
    char *end;
    char *value;

    end = start;
    while (*end && !ft_isspace((unsigned char)*end))
    end++;
    value = ft_substr(start, 0, (size_t)(end - start));
    if (!value)
    {
        *res = make_parse_error_result(P_ERR_MALLOC, NULL);
        return (NULL);
    }
    *end_out = end;
    *res = make_parse_succses_result();
    return (value);
}

static t_parse_result	validate_texture_path_parts(char *value, char *end, t_direction_key key)
{
	t_parse_result	res;
	char			*after_path;

	res = validate_texture_token(value, key);
	if (!res.ok)
		return (res);

    after_path = skip_spaces(end);
	if (*after_path != '\0' && *after_path != '\n')
		return (make_parse_error_result(P_ERR_TEXTURE_TRAILING, map_key(key)));
	return (make_parse_succses_result());
}

t_parse_result	fill_texture_path(char *line, char **path, t_direction_key key)
{
	char			*start;
	char			*end;
	char			*value;
	t_parse_result	res;

	if (*path != NULL)
		return (make_parse_error_result(P_ERR_DUP, map_key(key)));
	start = get_texture_value_start(line, key, &res);
	if (!res.ok)
		return (res);
    value = extract_texture_token(start, &end, &res);
	if (!res.ok)
		return (res);
	res = validate_texture_path_parts(value, end, key);
	if (!res.ok)
		return (free(value), res);
	*path = value;
	return (make_parse_succses_result());
}


// static t_parse_result fill_texture_path(char *line, char **path, t_direction_key key)
// {
//     char *value;
//     char *start;
//     char *end;
//     char *check_end;
//     size_t len;

//     if(*path != NULL)
//         return make_parse_error_result(P_ERR_DUP, map_key(key));
//     start = skip_spaces(line);
//     if(!start || *start == '\0'|| *start == '\n')
//         return make_parse_error_result(P_ERR_NO_PATH, map_key(key)); 
//     end = start;
//     while(*end && !ft_isspace(*end))
//         end++;
//     value = ft_substr(start, 0, (size_t)(end- start));
//     if(!value)
//         return(make_parse_error_result(P_ERR_MALLOC, NULL));

//     if(!xpm_extantion(value))
//     {
//         (free(value));
//         return make_parse_error_result(P_ERR_TEXTURE_EXT, map_key(key));
//     }

//     check_end = skip_spaces(end);
//     if (*check_end != '\0' && *check_end != '\n') 
//     {
//         free(value);
//         return(make_parse_error_result(P_ERR_TEXTURE_TRAILING, map_key(key)));

//     } 
//     *path = value;
//     return (make_parse_succses_result());
// }