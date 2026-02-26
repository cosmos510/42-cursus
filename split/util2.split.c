/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximemartin <maximemartin@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:41:22 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/18 10:15:54 by maximemarti      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**allocate_array(int word_count)
{
	return (calloc((word_count + 1), sizeof(char *)));
}

void	add_word_to_result(char **res, int j, char *word)
{
	res[j] = word;
	if (!res[j])
		free_array(res, j);
}

void	split_command(char *cmd, t_command *cmd_info)
{
	char	*first_space;
	char	*first_part;
	char	*rest;

	first_space = ft_strchr(cmd, ' ');
	if (first_space)
	{
		first_part = ft_substr(cmd, 0, first_space - cmd);
		rest = first_space + 1;
		cmd_info->tokens = ft_split2(rest, "\"");
	}
	else
	{
		first_part = ft_strdup(cmd);
		cmd_info->tokens = NULL;
	}
	if (cmd_info->tokens)
		cmd_info->tokens = ft_strjoin_arr(first_part, cmd_info->tokens);
	else
		cmd_info->tokens = ft_split2(first_part, "\'\"");
	free(first_part);
}