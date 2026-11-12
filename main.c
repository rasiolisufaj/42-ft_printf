/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raisufaj <raisufaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:04:36 by raisufaj          #+#    #+#             */
/*   Updated: 2026/11/12 00:00:00 by raisufaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Compiled twice by `make test`: once with -D PRINTF=printf and once with
** -D PRINTF=ft_printf. Each line also prints the return value, so both the
** output and the character count are compared.
*/
int	main(void)
{
	char	*null_str;

	null_str = NULL;
	PRINTF(" = %d\n", PRINTF("c: [%c] [%c]", 'a', '0'));
	PRINTF(" = %d\n", PRINTF("s: [%s] [%s] [%s]", "hello", "", null_str));
	PRINTF(" = %d\n", PRINTF("d: [%d] [%i] [%d] [%d]", 0, -42, INT_MAX,
			INT_MIN));
	PRINTF(" = %d\n", PRINTF("u: [%u] [%u] [%u]", 0, 42, UINT_MAX));
	PRINTF(" = %d\n", PRINTF("x: [%x] [%X] [%x] [%X]", 0, 255, UINT_MAX,
			3735928559u));
	PRINTF(" = %d\n", PRINTF("p: [%p] [%p] [%p]", (void *)0xdeadbeef,
			(void *)ULONG_MAX, NULL));
	PRINTF(" = %d\n", PRINTF("mix: %c %s %d %u %x %X %%", 'z', "str", -1,
			-1, -1, -1));
	PRINTF(" = %d\n", PRINTF("%s", ""));
	return (0);
}
