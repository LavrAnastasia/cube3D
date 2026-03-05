#ifndef GRAPHICS_TYPES_H
# define GRAPHICS_TYPES_H

# include "types.h"

typedef struct s_px_buffer
{
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_px_buffer;

typedef struct s_image_buffer
{
	void			*img;
	t_px_buffer		px;
	t_dimensions 	size;
}	t_image_buffer;

typedef struct s_sprites
{
	t_image_buffer north_texture;
	t_image_buffer south_texture;
	t_image_buffer east_texture;
	t_image_buffer west_texture;
}	t_sprites;

typedef struct s_graphics
{
	t_sprites	sprites;
}	t_graphics;


#endif