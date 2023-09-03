/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krchuaip <krchuaip@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 16:27:48 by krchuaip          #+#    #+#             */
/*   Updated: 2023/09/04 00:11:38 by krchuaip         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	read_next(t_state *fd_state)
{
	if (fd_state->token && fd_state->eof)
		return ;
	if (!fd_state->token)
	{
		fd_state->token = malloc(sizeof(t_token));
		fd_state->token->nbyte = 0;
		fd_state->end_token = fd_state->token;
		fd_state->token->next = NULL;
	}
	else if (!fd_state->eof)
	{
		fd_state->end_token->next = malloc(sizeof(t_token));
		fd_state->end_token = fd_state->end_token->next;
		fd_state->end_token->nbyte = 0;
		fd_state->end_token->next = NULL;
	}
	fd_state->token_size++;
	fd_state->end_token->nbyte = \
		read(fd_state->fd, fd_state->end_token->buff, BUFFER_SIZE);
	if (fd_state->end_token->nbyte == 0)
		fd_state->eof = 1;
}

void	get_next_line_byte(t_state *fd_state)
{
	size_t	index;
	t_token	*token;

	if (!fd_state->token)
		read_next(fd_state);
	if (fd_state->end_token->nbyte == (size_t)-1)
		return ;
	token = fd_state->token;
	while (token->nbyte)
	{
		index = (fd_state->nl_bytes + fd_state->offset) % BUFFER_SIZE;
		if (index > token->nbyte - 1)
			return ;
		if (token->buff[index] == '\n')
		{
			fd_state->nl_bytes++;
			return ;
		}
		fd_state->nl_bytes++;
		if (index == BUFFER_SIZE - 1)
		{
			read_next(fd_state);
			token = token->next;
		}
	}
}

void	consume_token(t_state *fd_state, char *str)
{
	size_t	index;
	t_token	*ptok;

	index = 0;
	while (index < fd_state->nl_bytes)
	{
		str[index] = fd_state->token->buff[fd_state->offset];
		fd_state->offset++;
		index++;
		if (fd_state->offset == fd_state->token->nbyte)
		{
			ptok = fd_state->token;
			fd_state->token = fd_state->token->next;
			free(ptok);
			fd_state->offset = 0;
			fd_state->token_size--;
		}
	}
}

char	*get_next_line(int fd)
{
	static t_state	fd_state[FD_MAX];
	char			*str;

	if (fd < 0 || fd >= FD_MAX)
		return (NULL);
	if (fd_state[fd].eof && fd_state[fd].finish)
		return (NULL);
	if (!fd_state[fd].token)
	{
		fd_state[fd].fd = fd;
		fd_state[fd].offset = 0;
		fd_state[fd].token_size = 0;
	}
	fd_state[fd].nl_bytes = 0;
	get_next_line_byte(&fd_state[fd]);
	if (fd_state[fd].nl_bytes == 0 || fd_state[fd].token->nbyte == (size_t)-1)
	{
		free(fd_state[fd].token);
		fd_state[fd].finish = 1;
		return (NULL);
	}
	str = malloc(fd_state[fd].nl_bytes + 1);
	consume_token(&fd_state[fd], str);
	str[fd_state[fd].nl_bytes] = '\0';
	return (str);
}
