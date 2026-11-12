/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:34:38 by raisufaj          #+#    #+#             */
/*   Updated: 2026/11/12 00:00:00 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_ptr(void *ptr)
{
	if (!ptr)
		return (print_string("(nil)"));
	return (print_string("0x") + print_base((unsigned long)ptr, HEX_LOW));
}

static int	check_type(char c, va_list *args)
{
	if (c == 'c')
		return (print_char(va_arg(*args, int)));
	else if (c == 'd' || c == 'i')
		return (print_int(va_arg(*args, int)));
	else if (c == 's')
		return (print_string(va_arg(*args, char *)));
	else if (c == 'u')
		return (print_base(va_arg(*args, unsigned int), DEC));
	else if (c == 'x')
		return (print_base(va_arg(*args, unsigned int), HEX_LOW));
	else if (c == 'X')
		return (print_base(va_arg(*args, unsigned int), HEX_UP));
	else if (c == 'p')
		return (print_ptr(va_arg(*args, void *)));
	else if (c == '%')
		return (print_char('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_len;

	va_start(args, format);
	total_len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (!*format)
				break ;
			total_len += check_type(*format, &args);
		}
		else
			total_len += print_char(*format);
		format++;
	}
	va_end(args);
	return (total_len);
}
