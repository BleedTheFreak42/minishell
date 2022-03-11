/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaya <ytaya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 01:51:50 by ael-ghem          #+#    #+#             */
/*   Updated: 2022/03/11 09:38:01 by ytaya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_atoi(const char *nptr)
{
	unsigned long long			number;
	int							sign;
	int							i;
	int							n;

	i = 0;
	sign = 1;
	number = 0;
	if (nptr)
	{
		while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
			i++;
		if (nptr[i] == '-' || nptr[i] == '+')
			if (nptr[i++] == '-')
				sign = -1;
		n = i;
		while (nptr[i] >= '0' && nptr[i] <= '9')
			number = number * 10 + (nptr[i++] - 48);
	}
	return (number * sign);
}
