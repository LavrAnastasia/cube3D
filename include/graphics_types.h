#ifndef GRAPHICS_TYPES_H
# define GRAPHICS_TYPES_H

typedef struct s_px_buffer
{
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
}	t_px_buffer;

#endif