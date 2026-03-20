
#include "reporter_internal.h"

const char	*render_msg(int code)
{
	static const char	*map[] = {
		[RENDER_ERR_FALLBACK] = "Render: using fallback wall color",
		[RENDER_ERR_RAY_INTERSECTION] = "Render: ray intersection failed"
	};
	const int			size = sizeof(map) / sizeof(*map);

	if (code < 0 || code >= size)
		return (NULL);
	return (map[code]);
}