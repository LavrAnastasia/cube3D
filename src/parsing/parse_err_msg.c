#include "parsing_internal.h"

const char	*err_parse_msg(int code)
{
	int	size;

	static const char *map[] = {
		[P_ERR_MALLOC] = "Malloc failed",
		[P_ERR_NOT_COLOR] = "Colors not assigned",
		[P_ERR_EMPTY_FILE] = "The .cub file is empty",
		[P_ERR_NO_PATH] = "Texture path is missing",
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
		[P_ERR_INVALID_CONFIG_LINE] = "Expected NO/SO/WE/EA/F/C or map row",
		[P_ERR_MAP_NOT_CLOSED] = "Map is open to empty space or outside map bounds",
		[P_ERR_EMPTY_MAP] = "Map section is missing or empty",
		[P_ERR_MAP_EMPTY_LINE] = "Empty line inside map is not allowed"};
	size = sizeof(map) / sizeof(*map);
	if (code < 0 || code >= size)
		return (NULL);
	return (map[code]);
}

void	print_error_msg(const char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	print_error_key(const char *key, const char *msg)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	if (key && *key)
	{
		ft_putstr_fd((char *)key, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}