/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 23:29:18 by cosmos            #+#    #+#             */
/*   Updated: 2025/02/01 15:57:59 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	get_next_line_pip(char **output_line)
{
	char	*temp_buffer;
	int		char_count;
	int		bytes_read;
	char	current_char;

	char_count = 0;
	bytes_read = 0;
	temp_buffer = (char *)malloc(10000);
	if (!temp_buffer)
		return (-1);
	bytes_read = read(0, &current_char, 1);
	while (bytes_read && current_char != '\n' && current_char != '\0')
	{
		if (current_char != '\n' && current_char != '\0')
			temp_buffer[char_count] = current_char;
		char_count++;
		bytes_read = read(0, &current_char, 1);
	}
	temp_buffer[char_count] = '\n';
	temp_buffer[++char_count] = '\0';
	*output_line = temp_buffer;
	return (bytes_read);
}

void	here_doc(char *limiter, int *fd)
{
	char	*line;

	create_pipe(fd);
	while (get_next_line_pip(&line))
	{
		if (ft_strlen(line) - 1 == ft_strlen(limiter) && \
		ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(fd[1]);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
}

int	setup_io(int ac, char **av, int mode, int *fileout)
{
	int	filein;
	int	fd[2];

	filein = -1;
	if (mode == 1)
	{
		here_doc(av[2], fd);
		dup2(fd[0], STDIN_FILENO);
		*fileout = open_file(av[ac - 1], 2);
		close(fd[0]);
		if (fileout[0] == -1)
			error();
	}
	else
	{
		filein = open_file(av[1], 0);
		dup2(filein, STDIN_FILENO);
		*fileout = open_file(av[ac - 1], 1);
	}
	dup2(*fileout, STDOUT_FILENO);
	if (filein == -1)
		return (-1);
	return (0);
}

void	child_process_here_doc(char **env, char *cmd, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_it(fd);
	}
	if (pid == 0)
	{
		if (close(fd[0]) == -1)
			error();
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			error();
		execute(env, cmd);
	}
	else
	{
		if (close(fd[1]) == -1)
			error();
		if (dup2(fd[0], STDIN_FILENO) == -1)
			error();
		if (waitpid(pid, NULL, 0) == -1)
			close_it(fd);
	}
}
