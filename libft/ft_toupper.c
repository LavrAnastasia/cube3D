/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:34:02 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:22:12 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islowercase(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_toupper(int c)
{
	if (ft_islowercase(c))
		return (c - ('a' - 'A'));
	return (c);
}
