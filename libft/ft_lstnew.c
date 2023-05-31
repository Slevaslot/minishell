/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mblal <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:16:04 by slevaslo          #+#    #+#             */
/*   Updated: 2023/05/31 16:59:34 by mblal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*valreturn;

	valreturn = malloc(sizeof(t_list));
	if (!valreturn)
		return (NULL);
	valreturn->next = NULL;
	valreturn->content = content;
	return (valreturn);
}
