/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:17:01 by audobnai          #+#    #+#             */
/*   Updated: 2025/05/13 18:17:19 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>

int		ft_print_p(const uintptr_t ptr);
int		ft_print_uint(const unsigned int un);
int		ft_print_int(const int n);
int		ft_print_str(const char *s);
int		ft_print_char(const char c);
int		ft_puthex(unsigned int num, int uppercase, int leading_zero);
void	ft_try_add(int *count, int result);
#endif