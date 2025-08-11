/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gita <gita@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:33:56 by gita              #+#    #+#             */
/*   Updated: 2025/08/11 22:10:26 by gita             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	examination(va_list *ap, char check)
{
	if (check == '%')
		return (writechar('%'));
	if (check == 'c')
		return (writechar(va_arg(*ap, unsigned int)));
	if (check == 's')
		return (writestr(va_arg(*ap, char *)));
	if (check == 'd' || check == 'i')
		return (normal_num(va_arg(*ap, int)));
	if (check == 'u')
		return (fancy_num(va_arg(*ap, unsigned int), "0123456789"));
	if (check == 'x')
		return (fancy_num(va_arg(*ap, unsigned int), "0123456789abcdef"));
	if (check == 'X')
		return (fancy_num(va_arg(*ap, unsigned int), "0123456789ABCDEF"));
	if (check == 'p')
		return (finger(va_arg(*ap, uintptr_t), "0123456789abcdef"));
	return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	reservation;
	int		printed;
	int		check;

	printed = 0;
	va_start(reservation, format);
	if (format == NULL)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			check = examination(&reservation, *format);
		}
		else
			check = writechar(*format);
		if (check == -1)
			return (va_end(reservation), -1);
		else
			printed += check;
		format++;
	}
	va_end(reservation);
	return (printed);
}
