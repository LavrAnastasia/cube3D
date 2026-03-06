# include "textures_internal.h"

void texture_destroy(void *mlx_session, t_image_buffer *buffer)
{
	if (buffer->img == NULL)
		return;
	mlx_destroy_image(mlx_session, buffer->img);
	buffer->img = NULL;
	buffer->px.data = NULL;
}