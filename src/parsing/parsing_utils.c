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
	[P_ERR_NO_MAP] = "Please provide a .cub map file",
	[P_ERR_NO_PATH] = "Texture path is missing",
	[P_ERR_ARG] = "Too many arguments provided, required: program + map",
	[P_ERR_EXTENSION] = "Map must have .cub extension",
	[P_ERR_OPEN_FILE] = "Cannot open the file",
	[P_ERR_RGB] = "Invalid RGB format",
	[P_ERR_RGB_RANGE] = "RGB out of range",
	[P_ERR_DUP] = "There can be only one key",
    [P_ERR_TEXTURE_TRAILING] = "Exture path contains extra data",
    [P_ERR_TEXTURE_EXT] = "Texture file must have .xpm extension"};
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

void free_split(char **arr)
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