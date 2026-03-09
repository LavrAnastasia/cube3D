#include <math.h>
#include "movement.h"
#include "map_utils.h"
#include "math_u.h"


void	update_player_movement(t_scene *scene, const t_controls_state *controls)
{

	// TODO: cal gettimeofday and step

	// TODO: FUNC ANGLE
	const double rotation_step = 0.05;
	int turn_step;

	turn_step = 0;

	if (controls->turn_left)
		turn_step--;
	if(controls->turn_right)
		turn_step++;
	if (turn_step)
		scene->player.angle = normalize_angle(scene->player.angle + turn_step * rotation_step);

	// TODO: FUNC POSITION
	const double player_hit_radius = 0.25;
	const double eps = 1e-6;
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
	if (fabs(move_x) < eps)
		move_x = 0.0;
	if (fabs(move_y) < eps)
		move_y = 0.0;

	if (move_x == 0.0 && move_y == 0.0)
    	return;
	const double step = 0.25;

	t_position next_position = scene->player.pos;

	// TODO: ask ppl about collision 
	// personally I prefer thi way
	if (x_step != 0 && y_step != 0)
	{

		double x_position_candidate = scene->player.pos.x + move_x * step;
		double x_probe = x_position_candidate + sign(move_x) * player_hit_radius;
		// TODO: RENAME -- Player hit box sides
		t_point x_point_top = (t_point){
			.x = (int)floor(x_probe),
			.y = (int)floor(scene->player.pos.y - player_hit_radius)
		};
		t_point x_point_bottom = (t_point){
			.x = (int)floor(x_probe),
			.y = (int)floor(scene->player.pos.y + player_hit_radius)
		};
		if (is_in_bounds(x_point_top, scene->map_size)
			&& is_in_bounds(x_point_bottom, scene->map_size)
			&& !is_wall(x_point_top, scene->map)
			&& !is_wall(x_point_bottom, scene->map))
		{
			next_position.x = x_position_candidate;
		}

		double y_position_candidate = scene->player.pos.y + move_y * step;
		double y_probe = y_position_candidate + sign(move_y) * player_hit_radius;
		t_point y_point_left = (t_point){
			.x = (int)floor(next_position.x - player_hit_radius),
			.y = (int)floor(y_probe)
		};
		t_point y_point_right = (t_point){
			.x = (int)floor(next_position.x + player_hit_radius),
			.y = (int)floor(y_probe)
		};

		if (is_in_bounds(y_point_left, scene->map_size)
			&& is_in_bounds(y_point_right, scene->map_size)
			&& !is_wall(y_point_left, scene->map)
			&& !is_wall(y_point_right, scene->map))
		{
			next_position.y = y_position_candidate;
		}
	}
	else
	{
		double x_position_candidate = scene->player.pos.x + move_x * step;
		double y_position_candidate = scene->player.pos.y + move_y * step;
		// TODO: RENAME -- Player hit box sides
		t_point x_point_top = (t_point){ .x = (int)floor(x_position_candidate - player_hit_radius), .y = (int)floor(y_position_candidate - player_hit_radius) };
		t_point x_point_bottom = (t_point){ .x = (int)floor(x_position_candidate + player_hit_radius), .y = (int)floor(y_position_candidate - player_hit_radius) };
		t_point y_point_left = (t_point){ .x = (int)floor(x_position_candidate - player_hit_radius), .y = (int)floor(y_position_candidate + player_hit_radius) };
		t_point y_point_right = (t_point){ .x = (int)floor(x_position_candidate + player_hit_radius), .y = (int)floor(y_position_candidate + player_hit_radius) };

		if (is_in_bounds(x_point_top, scene->map_size) && !is_wall(x_point_top, scene->map)
			&& is_in_bounds(x_point_bottom, scene->map_size) && !is_wall(x_point_bottom, scene->map)
			&& is_in_bounds(y_point_left, scene->map_size) && !is_wall(y_point_left, scene->map)
			&& is_in_bounds(y_point_right, scene->map_size) && !is_wall(y_point_right, scene->map))
		{
			next_position.x = x_position_candidate;
			next_position.y = y_position_candidate;
		}

	}

	scene->player.pos = next_position;
	
}