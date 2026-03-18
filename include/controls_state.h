/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_state.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 23:00:50 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/18 23:03:56 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_STATE_H
# define CONTROLS_STATE_H

# include <stdbool.h>

typedef struct s_controls_state
{
	bool	move_forward;
	bool	move_backward;
	bool	move_left;
	bool	move_right;
	bool	turn_left;
	bool	turn_right;
	bool	quit_requested;
}	t_controls_state;

#endif