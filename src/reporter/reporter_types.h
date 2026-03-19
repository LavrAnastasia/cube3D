#ifndef REPORTER_TYPES_H
# define REPORTER_TYPES_H

typedef enum e_reporter_domain
{
	D_ENGINE = 0,
	D_SCENE,
	D_TEXTURES,
	D_RENDER
}	t_reporter_domain;

typedef enum e_severity_level
{
	SL_WARNING = 0,
	SL_ERROR
}	t_severity_level;

#endif