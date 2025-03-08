/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 20:28:15 by cosmos            #+#    #+#             */
/*   Updated: 2025/02/01 15:58:13 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
//path_utils
char	**find_path_env(char **env);
char	**add_slash(char **path);
char	*find_path(char **path, char *arg);
char	**process_path_string(char *path_str);
char	*get_path_string(char **env);
//free_it
void	free_it(char **s);
void	error(void);
void	error2(char **path_env, char **args);
void	clean_up(char **path_env, char **args, char *path);
void	close_it(int *fd);
//commande_utlis.c
char	*find_command_path(char **path_dirs, char **args);
char	**create_command_args(char *cmd);
char	**create_args(char **temp, char **args, int count);
//execute.c
void	execute(char **env, char *arg);
void	child_process(char **env, char *cmd, int *fd, int file);
void	handle_pipes(int ac, char **av, char **env);
int		open_file(char *file, int mode);
int		create_pipe(int *fd);
//execute_bonus
void	handle_pipes_bonus(int ac, char **av, char **env, int mode);
//utils_bonus
int		get_next_line_pip(char **line);
void	here_doc(char *limiter, int *fd);
int		setup_io(int ac, char **av, int mode, int *fileout);
void	child_process_here_doc(char **env, char *cmd, int *fd);

#endif