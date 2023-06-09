/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:55:26 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 16:57:41 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t count)
{
	unsigned char	*str;
	size_t			i;

	str = ptr;
	i = 0;
	while (i < count)
	{
		str[i] = '\0';
		i++;
	}
}
