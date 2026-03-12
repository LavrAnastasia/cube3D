#ifndef MOVEMENT_INNER_H
# define MOVEMENT_INNER_H

# include "scene.h"
# include "controls_state.h"

typedef struct s_move_intent {
	int x;
	int y;
} t_move_intent;

double	get_current_time_seconds(void);
double	get_frame_delta_seconds(
	double current_time_seconds,
	double last_update_time_seconds
);

#endif