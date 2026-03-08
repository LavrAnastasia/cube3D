# include <mlx.h>
# include "textures_types.h"

void	*load_xpm(void *mlx_session, const char *path, t_dimensions *size)
{
	return (
		mlx_xpm_file_to_image(
			mlx_session,
			(char *)path,
			&size->width,
			&size->height
		)
	);
}

char	*load_px_data(t_image_buffer *buffer)
{
	return (
		mlx_get_data_addr(
		buffer->img,
		&buffer->px.bpp,
		&buffer->px.line_len,
		&buffer->px.endian)
	);
}
