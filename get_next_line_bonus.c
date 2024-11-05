/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:20:14 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/04 15:20:15 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	linked_next_call(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;

	if (!*list)
		return ;
	last_node = found_last_node(*list);
	if (!last_node)
		return ;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	clean_node = malloc(sizeof(t_list));
	i = 0;
	j = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	if (last_node->str_buf[i] == '\n')
		i++;
	while (last_node->str_buf[i])
		buf[j++] = last_node->str_buf[i++];
	buf[j] = '\0';
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	clean(list, clean_node, buf);
}

char	*start_line(t_list *list)
{
	int		str_len;
	char	*next_temp;

	if (list == NULL)
		return (NULL);
	str_len = next_len(list);
	next_temp = malloc(str_len + 1);
	if (next_temp == NULL)
		return (NULL);
	ft_strcpy(list, next_temp);
	return (next_temp);
}

void	appended_words(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = found_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_new_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buf);
			clean(list, NULL, NULL);
			*list = NULL;
			return ;
		}
		if (char_read == 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		appended_words(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[4096];
	char			*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE == 0 || read(fd, next_line, 0) < 0)
	{
		clean(&list[fd], NULL, NULL);
		return (NULL);
	}
	create_list(&list[fd], fd);
	if (list[fd] == NULL)
		return (NULL);
	next_line = start_line(list[fd]);
	linked_next_call(&list[fd]);
	if (!next_line)
	{
		clean(&list[fd], NULL, NULL);
		list[fd] = NULL;
	}
	return (next_line);
}
