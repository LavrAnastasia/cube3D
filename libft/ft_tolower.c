/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:59 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:26:13 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isuppercase(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_tolower(int c)
{
	if (ft_isuppercase(c))
		return (c + ('a' - 'A'));
	return (c);
}
