/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_array_sorted.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 14:11:46 by audobnai          #+#    #+#             */
/*   Updated: 2025/08/05 14:11:49 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_array_sorted(int *arr, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (arr[i - 1] > arr[i])
			return (0);
		i++;
	}
	return (1);
}
