/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krchuaip <krchuaip@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:28:09 by krchuaip          #+#    #+#             */
/*   Updated: 2023/12/13 19:45:30 by krchuaip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define FD_MAX	1024
# ifndef GNL_BUFFER_SIZE
#  define GNL_BUFFER_SIZE 256
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

//
// # include <stdio.h>
//

typedef struct s_token
{
	char			buff[GNL_BUFFER_SIZE];
	struct s_token	*next;
	size_t			nbyte;
}	t_token;

typedef struct s_state
{
	int				fd;
	int				eof;
	int				finish;
	t_token			*token;
	t_token			*end_token;
	size_t			offset;
	size_t			nl_bytes;
	size_t			token_size;
}	t_state;

char	*get_next_line(int fd);

#endif
