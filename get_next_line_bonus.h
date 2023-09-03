/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krchuaip <krchuaip@student.42bangkok.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:28:09 by krchuaip          #+#    #+#             */
/*   Updated: 2023/09/03 23:28:28 by krchuaip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define FD_MAX	1000
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>

//
// # include <stdio.h>
//

typedef struct s_token
{
	char			buff[BUFFER_SIZE];
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
