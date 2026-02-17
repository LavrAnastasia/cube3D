/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:54:45 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 15:24:18 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_rec(long n, int fd)
{
	char	tmp;

	if (n == 0)
		return ;
	ft_putnbr_fd_rec(n / 10, fd);
	tmp = (n % 10) + '0';
	write(fd, &tmp, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nc;

	nc = (long)n;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		nc *= -1;
	}
	ft_putnbr_fd_rec(nc, fd);
}
