/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audobnai <audobnai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 12:54:03 by audobnai          #+#    #+#             */
/*   Updated: 2025/04/22 16:30:09 by audobnai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list	*lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*head;
	t_list	*tail;

	head = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		new_list = malloc(sizeof(t_list));
		if (!new_list)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new_list->content = (*f)(lst->content);
		new_list->next = NULL;
		if (!head)
			head = new_list;
		else
			tail->next = new_list;
		tail = new_list;
		lst = lst->next;
	}
	return (head);
}
