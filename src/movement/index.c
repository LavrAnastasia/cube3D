#include <math.h>
#include "movement.h"
#include "map_utils.h"
#include "math_u.h"

void	update_player_movement(t_scene *scene, const t_controls_state *controls)
{

	// TODO: FUNC ANGLE
	const double rotation_step = 0.05;
	int turn_step;

	turn_step = 0;

	if (controls->turn_left)
		turn_step--;
	if(controls->turn_right)
		turn_step++;

	scene->player.angle = normalize_angle(scene->player.angle + turn_step * rotation_step);

	// TODO: FUNC POSITION
	const double player_radius = 0.25;
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

	t_position next_position = scene->player.pos;

	double x_position_candidate = scene->player.pos.x + move_x * step;
	double x_probe = x_position_candidate + sign(move_x) * player_radius;
	t_point x_point_candidate = (t_point){ .x = (int)floor(x_probe), .y = (int)floor(scene->player.pos.y) };
	if (is_in_bounds(x_point_candidate, scene->map_size) && !is_wall(x_point_candidate, scene->map))
	{
		next_position.x = x_position_candidate;
	}

	double y_position_candidate = scene->player.pos.y + move_y * step;
	double y_probe = y_position_candidate + sign(move_y) * player_radius;
	t_point y_point_candidate = (t_point){ .x = (int)floor(next_position.x), .y = (int)floor(y_probe) };
	if (is_in_bounds(y_point_candidate, scene->map_size) && !is_wall(y_point_candidate, scene->map))
	{
		next_position.y = y_position_candidate;
	}

	scene->player.pos = next_position;
	
}