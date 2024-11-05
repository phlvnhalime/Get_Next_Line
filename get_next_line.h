/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:26:27 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/04 12:54:26 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

int					found_new_line(t_list *list);
t_list				*found_last_node(t_list *list);
int					next_len(t_list *list);
void				clean(t_list **list, t_list *clean_node, char *buf);
void				ft_strcpy(t_list *list, char *next_temp);
char				*get_next_line(int fd);

#endif
