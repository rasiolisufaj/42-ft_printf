/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:04:36 by raisufaj          #+#    #+#             */
/*   Updated: 2025/02/09 19:04:36 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	main(void)
{
	ft_printf("TEST NUMBERS: %i %d\n", INT_MAX, INT_MIN);
	printf("TEST NUMBERS: %i %d\n", INT_MAX, INT_MIN);
	ft_printf("%s %c%%\n", "", 'Z');
	printf("%s %c%%\n", "", 'Z');
	ft_printf("%d\n", -2147483648);
	printf("%ld\n", -2147483648);
	// ft_printf("%d", ft_printf("THIS IS A REBUILT %s\n", "FT_PRINTF"));
	// printf("%d", ft_printf("THIS IS A REBUILT %s\n", "FT_PRINTF"));
	return (0);
}
