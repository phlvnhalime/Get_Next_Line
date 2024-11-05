/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:24:39 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/04 12:54:14 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	linked_next_call(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;

	last_node = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	last_node = found_last_node(*list);
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

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->str_buf = buf;
	new_node->next = NULL;
	last_node = found_last_node(*list);
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
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
			return ;
		}
		if (char_read == 0)
		{
			free(buf);
			break ;
		}
		buf[char_read] = '\0';
		appended_words(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
	{
		clean(&list, NULL, NULL);
		return (NULL);
	}
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = start_line(list);
	linked_next_call(&list);
	return (next_line);
}

// #include <stdio.h>

// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("file.txt", O_RDONLY );
// 	if (fd < 0)
// 		if (fd < 0) {
//         perror("Failed to open file");
//         return (1); // Exit if the file cannot be opened
//     }

//     // Read lines until EOF
//     while ((line = get_next_line(fd)) != NULL) {
//         printf("%s", line); // Print the line read from the file
//         free(line);         // Free the memory allocated for the line
//     }

//     // Close the file descriptor
//     close(fd);
//     return (0); // Exit successfully
// }
