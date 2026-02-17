/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:10:38 by audobnai          #+#    #+#             */
/*   Updated: 2025/05/13 18:13:42 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_for(const char format_spec, va_list *arg)
{
	if (format_spec == 'c')
		return (ft_print_char(va_arg(*arg, int)));
	else if ((format_spec == 'i') || (format_spec == 'd'))
		return (ft_print_int(va_arg(*arg, int)));
	else if (format_spec == 's')
		return (ft_print_str(va_arg(*arg, char *)));
	else if (format_spec == 'u')
		return (ft_print_uint(va_arg(*arg, unsigned int)));
	else if ((format_spec == 'x') || (format_spec == 'X'))
		return (ft_puthex(va_arg(*arg, unsigned int), format_spec == 'X', 0));
	else if (format_spec == 'p')
		return (ft_print_p(va_arg(*arg, uintptr_t)));
	return (ft_print_char(format_spec));
}

int	ft_printf(const char *format, ...)
{
	va_list	list;
	int		result;
	size_t	i;

	if (!format)
		return (-1);
	va_start(list, format);
	i = 0;
	result = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1]
			&& ft_strchr("cspdiuxX%", format[i + 1]))
		{
			i++;
			ft_try_add(&result, ft_print_for(format[i], &list));
		}
		else
			ft_try_add(&result, ft_print_char(format[i]));
		if (result == -1)
			return (-1);
		i++;
	}
	va_end(list);
	return (result);
}
