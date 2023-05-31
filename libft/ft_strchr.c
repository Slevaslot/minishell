/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:08:48 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 17:00:34 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( const char *string, int searchedChar )
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)string;
	while (str[i] != '\0' && str[i] != (char)searchedChar)
	{
		i++;
	}
	if (str[i] != (char)searchedChar)
		return (NULL);
	return (&str[i]);
}
