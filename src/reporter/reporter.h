/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:21:43 by audobnai          #+#    #+#             */
/*   Updated: 2026/03/20 17:22:50 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPORTER_H
# define REPORTER_H

# include "reporter_types.h"

void	report(t_reporter_domain domain, int code, t_severity_level level);

#endif