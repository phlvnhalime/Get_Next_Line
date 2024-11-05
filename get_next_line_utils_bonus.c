/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:20:23 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/04 15:20:25 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	found_new_line(t_list *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*found_last_node(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

int	next_len(t_list *list)
{
	int	i;
	int	len;

	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && list->str_buf[i] != '\n')
		{
			len++;
			i++;
		}
		if (list->str_buf[i] == '\n')
		{
			len++;
			break ;
		}
		list = list->next;
	}
	return (len);
}

void	clean(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*ptr;

	if (*list == NULL)
		return ;
	while (*list)
	{
		ptr = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = ptr;
	}
	*list = NULL;
	if (clean_node && clean_node->str_buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

void	ft_strcpy(t_list *list, char *next_temp)
{
	int	i;
	int	k;

	k = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				next_temp[k++] = '\n';
				next_temp[k] = '\0';
				return ;
			}
			next_temp[k++] = list->str_buf[i++];
		}
		list = list->next;
	}
	next_temp[k] = '\0';
}
