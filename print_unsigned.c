/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:24:41 by raisufaj          #+#    #+#             */
/*   Updated: 2025/02/09 19:24:41 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n > 9)
		len += print_unsigned(n / 10);
	len += print_char((n % 10) + '0');
	return (len);
}
