#include <math.h>
#include "movement.h"
#include "map_utils.h"

void	update_player_movement(t_scene *scene, const t_controls_state *controls)
{
	int x_step;
	int y_step;

	x_step = 0;
	y_step = 0;
  
	if (controls->move_backward)
		y_step--; 
	if (controls->move_forward)
		y_step++; 
	if (controls->move_left)
		x_step--;
	if (controls->move_right)
		x_step++; 

	const double angle = scene->player.angle;
	const t_vector y_direction = (t_vector){.x = cos(angle), .y = sin(angle)};
	const t_vector x_direction = (t_vector){.x = -sin(angle), .y = cos(angle)};

	double move_x = y_step * y_direction.x + x_step * x_direction.x;
	double move_y = y_step * y_direction.y + x_step * x_direction.y;

	const double length = sqrt(move_x * move_x + move_y * move_y);

	if (length > 0)
	{
		move_x /= length;
		move_y /= length;
	}
	const double step = 0.25;

	t_position next_position = (t_position){
		.x = scene->player.pos.x + move_x * step,
		.y = scene->player.pos.y + move_y * step};

	t_point next_point;

	
	next_point = (t_point){ .x = (int)floor(next_position.x), .y = (int)floor(next_position.y) };
	if (is_in_bounds(next_point, scene->map_size) && !is_wall(next_point, scene->map))
	{
	    scene->player.pos = next_position;
	}
	
}