/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:33:08 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/17 15:30:03 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_islowercase(int c)
{
	return (c >= 'a' && c <= 'z');
}

static int	ft_isuppercase(int c)
{
	return (c >= 'A' && c <= 'Z');
}

int	ft_isalpha(int c)
{
	return (ft_islowercase(c) || ft_isuppercase(c));
}
