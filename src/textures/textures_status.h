#ifndef TEXTURES_STATUS_H
# define TEXTURES_STATUS_H

typedef enum e_textures_status
{
	TEX_OK = 0,
	TEX_ERR_LOAD_IMAGE,
	TEX_ERR_LOAD_PIXELS
}	t_textures_status;

#endif