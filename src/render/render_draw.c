#include "render_internal.h"

static void render_wall_fallback(size_t x, t_px_buffer *buffer, t_range range, t_color color);
static void render_wall_segment(t_wall_column column, t_px_buffer *buffer);

void render_vertical_segment(t_range range, size_t x, t_px_buffer *buffer, int color)
{
	size_t y;

	y = range.start;
	while (y < range.end)
	{
		pixels_put(buffer, x, y, color);
		y++;
	}	
}


void render_ceiling_and_floor(t_wall_column wall_column, size_t window_height, t_px_buffer *buffer, const t_palette *palette)
{
	render_vertical_segment(
		(t_range){.start = 0, .end = wall_column.projection.range.start},
		wall_column.x, buffer, palette->ceiling);
	render_vertical_segment(
		(t_range){.start = wall_column.projection.range.end, .end = window_height },
		wall_column.x, buffer, palette->floor);
}

void render_wall(t_wall_column wall_column, t_px_buffer *buffer)
{
	if (wall_column.projection.range.end <= wall_column.projection.range.start)
	{
		render_wall_fallback(wall_column.x, buffer, wall_column.projection.range, wall_column.fallback_color);
		return;
	}
	
	if (wall_column.sample.texture == NULL)
	{
		render_wall_fallback(wall_column.x, buffer, wall_column.projection.range, wall_column.fallback_color);
		return;
	}
	render_wall_segment(wall_column, buffer);
}

// TODO: trigger a warning
static void render_wall_fallback(size_t x, t_px_buffer *buffer, t_range range, t_color color)
{
	render_vertical_segment(range, x, buffer, color);
}

static void render_wall_segment(t_wall_column column, t_px_buffer *buffer)
{
	double			position_down_wall;
	int				texture_y;
	size_t			y;
	int				color;

	y = column.projection.range.start;
	while (y < column.projection.range.end)
	{
		position_down_wall = ((double)y - column.projection.top) / column.projection.height;
		texture_y = (int)floor(position_down_wall * column.sample.texture->size.height);

		texture_y = clamp(texture_y, 0, column.sample.texture->size.height - 1);

		color = pixels_get(&column.sample.texture->px, column.sample.texture_x, texture_y);
		pixels_put(buffer, column.x, y, color);
		y++;
	}
}
