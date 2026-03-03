# include <mlx.h>
# include "graphics.h"

void	*load_xpm(void *mlx_session, const char *path, int size)
{
	return (
		mlx_xpm_file_to_image(
			mlx_session,
			(char *)path,
			&size,
			&size
		)
	);
}

