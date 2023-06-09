/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:37:02 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 16:58:18 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*itoa_formule(int nb, int i, int j, char *str)
{
	if (nb < 0)
	{
		nb = nb * (-1);
		str[j] = '-';
		j = i - 1;
		while (j >= 1)
		{
			str[j] = nb % 10 + '0';
			nb = nb / 10;
			j--;
		}
	}
	else
	{
		j = i - 1;
		while (j >= 0)
		{
			str[j] = nb % 10 + '0';
			nb = nb / 10;
			j--;
		}
	}
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		nb;
	int		j;

	j = 0;
	i = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nb = n;
	if (nb < 0)
	{
		nb = nb * (-1);
		i++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		i++;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	itoa_formule (n, i, j, str);
	return (str);
}
