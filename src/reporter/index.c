#include <unistd.h>
#include <stddef.h>

#include "libft.h"
#include "reporter_types.h"
#include "reporter_internal.h"
#include "engine_status.h"
#include "textures_status.h"
#include "scene_status.h"

static const char	*engine_msg(int code)
{
	static const char	*map[] = {
		[ENGINE_ERR_INIT_MLX] = "Mlx: could not be inited",
		[ENGINE_ERR_CREATE_WINDOW] = "Mlx: could not create window",
		[ENGINE_ERR_CREATE_IMAGE] = "Mlx: could not create iamge",
		[ENGINE_ERR_GET_IMAGE_DATA] = "Mlx: could not get data from image"
	};
	const int			size = sizeof(map) / sizeof(*map);

	if (code < 0 || code >= size)
		return (NULL);
	return (map[code]);
}

static const char	*textures_msg(int code)
{
	static const char	*map[] = {
		[TEX_ERR_LOAD_IMAGE] = "Mlx: could not load texture image",
		[TEX_ERR_LOAD_PIXELS] = "Mlx: could not get data from texture image"
	};
	const int			size = sizeof(map) / sizeof(*map);

	if (code < 0 || code >= size)
		return (NULL);
	return (map[code]);
}

static const char	*scene_msg(int code)
{
	static const char	*map[] = {
		[SC_ERR_MALLOC] = "Scene can not be created (not enough space)"
	};
	const int			size = sizeof(map) / sizeof(*map);

	if (code < 0 || code >= size)
		return (NULL);
	return (map[code]);
}

static const char	*(*msg_resolver(t_reporter_domain domain))(int c)
{
	static const char	*(*table[])(int) = {
		[D_ENGINE] = engine_msg,
		[D_SCENE] = scene_msg,
		[D_TEXTURES] = textures_msg,
		[D_RENDER] = render_msg};
	const size_t		size = sizeof table / sizeof * table;

	if (domain < 0 || domain >= size)
		return (NULL);
	return (table[domain]);
}

void report(t_reporter_domain domain, int code, t_severity_level level)
{
	const char	*(*resolver)(int) = msg_resolver(domain);
	const char	*message;

	message = NULL;
	if (level == SL_ERROR)
		ft_putendl_fd("Error", STDERR_FILENO);
	else if (level == SL_WARNING)
		ft_putendl_fd("WARNING", STDERR_FILENO);
	if (resolver)
		message = resolver(code);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO); 
}