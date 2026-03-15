#ifndef TEXTURES_TYPES_H
# define TEXTURES_TYPES_H

# include "types.h"


typedef struct s_wall_texture_paths {
	char	*north;
	char	*south;
	char	*west;
	char	*east;
} t_wall_texture_paths;

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

typedef struct s_wall
{
	t_image_buffer north;
	t_image_buffer south;
	t_image_buffer east;
	t_image_buffer west;
}	t_wall;

typedef struct s_textures
{
	t_wall	wall;
}	t_textures;


#endif