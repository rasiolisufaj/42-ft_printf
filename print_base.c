/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 00:00:00 by raisufaj          #+#    #+#             */
/*   Updated: 2026/11/12 00:00:00 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_base(unsigned long n, char *base)
{
	unsigned long	len;
	int				count;

	len = ft_strlen(base);
	count = 0;
	if (n >= len)
		count = print_base(n / len, base);
	return (count + print_char(base[n % len]));
}
