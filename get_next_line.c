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
/*
	linked_next_call -- Updates the linked list to handle data after the newline.
			    Moves the remaining data from the last node's buffer 
			    to a new node and clears the buffer of the old node.
 * @list: Pointer to head of the linked list.
*/
	
void	linked_next_call(t_list **list)
{
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		j;
	char	*buf;

	// Initialized pointers and allocate buffer for remaining characters.
	last_node = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (buf == NULL || clean_node == NULL)
		return ;
	// Find the last node in the list where the newline is located.
	last_node = found_last_node(*list);
	i = 0;
	j = 0;
	// Move past the newline in the buffer!
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	if (last_node->str_buf[i] == '\n')
		i++;
	// Copy remaining characters after newline into the new buffer.
	while (last_node->str_buf[i])
		buf[j++] = last_node->str_buf[i++];
	buf[j] = '\0'; // NULL-terminate the buffer.
	clean_node->str_buf = buf;
	clean_node->next = NULL;
	// Call clean to handle the linked list cleanup and management.
	clean(list, clean_node, buf);
}
/**
 * start_line - Creates a string from the linked list up to the first newline.
 * @list: Linked list holding buffered data.
 * 
 * Return: A pointer to the allocated string with the data before the newline.
 */
char	*start_line(t_list *list)
{
	int		str_len;
	char	*next_temp;

	if (list == NULL)
		return (NULL);
	// Calculate the length of the string up the first newline.
	str_len = next_len(list);
	next_temp = malloc(str_len + 1);
	if (next_temp == NULL)
		return (NULL);
	// Copy the characters up to the newline into next_temp.
	ft_strcpy(list, next_temp);
	return (next_temp);
}
/*
	Appended_words -- Appends a new node with the buffer content to the linked list.
 * @list: Pointer to the head of the linked list.
 * @buf: String containing the data to append to the list.
 */
void	appended_words(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	// Allocate memory for a new node.
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->str_buf = buf;
	new_node->next = NULL;
	// Find the last node and append the new node.
	last_node = found_last_node(*list);
	if (last_node == NULL)
		*list = new_node;
	else
		last_node->next = new_node;
}
/*
	create_list -- Reads data from a file descriptor and stores it in
 			a linked list until a newline character is found.
 * @list: Pointer to the head of the linked list.
 * @fd: File directoy to read data from.
*/

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;
	// Keep reading until we find a newline !
	while (!found_new_line(*list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return ;
		// read character into the buffer!
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			// Free buffer and clean list if there's a read error
			free(buf);
			clean(list, NULL, NULL);
			return ;
		}
		if (char_read == 0)
		{
			// Free buffer and exit if we reach EOF
			free(buf);
			break ;
		}
		buf[char_read] = '\0'; // NULL terminate the buffer!
		// Append the buffer to the linked list.
		appended_words(list, buf);
	}
}
/*
	get_next_line -- Main function to return the next line from a file descriptor
			Reads data into a linked list and returns one line at a time.
* @fd: File Descriptor to read data from.

* Return: A pointer to next line read from the file descriptor.
*/
char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	next_line = NULL;
	// Check and return file descriptor and BUFFER_SIZE
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
	{
		// Clean and return NULL if invalid parameters or read fails.
		clean(&list, NULL, NULL);
		return (NULL);
	}
	// Create the linked list with the file's data.
	create_list(&list, fd);
	if (list == NULL)
		return (NULL);
	// Extract the line up the newline character.
	next_line = start_line(list);
	// Prepare for the next call y updating the linked list.
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
