/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:17:35 by raisufaj          #+#    #+#             */
/*   Updated: 2025/02/09 18:17:35 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(int num)
{
	long			nb;
	unsigned int	len;

	nb = num;
	len = 1;
	if (nb < 0)
	{
		ft_putchar_fd('-', 1);
		nb = -nb;
		len++;
	}
	if (nb > 9)
		len += print_int(nb / 10);
	ft_putchar_fd(nb % 10 + '0', 1);
	if (num == -2147483648)
		return (11);
	return (len);
}
