#include "parsing.h"

char *skip_spaces(char *s)
{
    if(!s)
        return (NULL);
    while (ft_isspace(*s))
        s++;
    return(s);
}
//# define ERR_MAP "Map section is missing"  -- TODO: find this message

const char	*err_parse_msg(int code)
{
	static const char	*map[] = {
	[P_ERR_MALLOC] = "Malloc failed",
	[P_ERR_NO_INPUT_FILE] = "Please provide a .cub file",
    [P_ERR_EMPTY_FILE] = "The .cub file is empty",
	[P_ERR_NO_PATH] = "Texture path is missing",
	[P_ERR_ARG] = "Too many arguments provided, required: program + map",
	[P_ERR_EXTENSION] = "Map must have .cub extension",
	[P_ERR_OPEN_FILE] = "Cannot open the file",
	[P_ERR_RGB] = "Invalid RGB format",
	[P_ERR_RGB_RANGE] = "RGB out of range",
	[P_ERR_DUP] = "There can be only one key",
    [P_ERR_TEXTURE_TRAILING] = "Texture path contains extra data",
    [P_ERR_TEXTURE_EXT] = "Texture file must have .xpm extension",
    [P_ERR_INVALID_SYMBOLS] = "The map contains extraneous symbols",
    [P_ERR_PLAYER_COUNT] = "Map must contain exactly one player start",
    [P_ERR_DUP_FLOOR] = "There can be only one floor color",
    [P_ERR_DUP_CEILING] = "There can be only one ceiling color",
    [P_ERR_NOT_COLOR] = "Colors not assigned",
    [P_ERR_INVALID_CONFIG_LINE] = "Invalid .cub file line: expected NO/SO/WE/EA/F/C or map row",
    [P_ERR_MAP_NOT_CLOSED] = "Map is not closed: open to empty space or outside map bounds",
    [P_ERR_EMPTY_MAP] = "Map section is missing or empty",
    [P_ERR_MAP_EMPTY_LINE] = "Empty line inside map is not allowed"};
	const int			size = sizeof(map) / sizeof(*map);

	if (code < 0 || code >= size)
		return (NULL);
	return (map[code]);
}

void print_parse_error(t_parse_error error)
{   
    if (error.info != NULL)
        print_error_key(error.info, err_parse_msg(error.code));
    else
        print_error_msg(err_parse_msg(error.code));

}
void print_error_msg(const char *msg)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    ft_putendl_fd(msg, STDERR_FILENO);
}

void	print_error_key(const char *key, const char *msg)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    if(key && *key)
    {
        ft_putstr_fd((char *)key, STDERR_FILENO);
        ft_putstr_fd(":", STDERR_FILENO);
    }
    ft_putendl_fd(msg, STDERR_FILENO);
}

int parse_clean(int fd, char *line)
{
    free(line);
    close(fd);
    return(1);
}

void free_str_array(char **arr)
{
    int i;

    if(!arr)
        return ;
    i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}