/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cosmos <cosmos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:50:23 by cosmos            #+#    #+#             */
/*   Updated: 2025/03/11 11:07:39 by cosmos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	extract_and_add_word(t_split_data *data, size_t i)
{
	int	end;

	end = get_end(data->s, i, data->delimiters);
	add_word_to_result(data->res, *(data->j), \
	create_word(data->s, *(data->s_word), end));
	*(data->s_word) = -1;
	(*(data->j))++;
}

static void	handle_split_logic(t_split_data *data)
{
	size_t	i;
	size_t	end_index;

	i = 0;
	while (data->s[i])
	{
		if (!is_delimiter(data->s[i], data->delimiters) && *(data->s_word) < 0)
			*(data->s_word) = i;
		if ((is_delimiter(data->s[i], data->delimiters) || \
		data->s[i + 1] == '\0') && *(data->s_word) >= 0)
		{
			if (is_delimiter(data->s[i], data->delimiters))
				end_index = i - 1;
			else
				end_index = i;
			extract_and_add_word(data, end_index);
			*(data->s_word) = -1;
		}
		i++;
	}
}

static int	count_words(const char *str, const char *delimiters)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*str)
	{
		if (!is_delimiter(*str, delimiters) && !in_word)
		{
			in_word = true;
			count++;
		}
		else if (is_delimiter(*str, delimiters))
			in_word = false;
		str++;
	}
	return (count);
}

static char	**setup_split(const char *s, const char *delimiters)
{
	int				j;
	int				s_word;
	int				word_count_result;
	char			**res;
	t_split_data	data;

	word_count_result = count_words(s, delimiters);
	res = allocate_array(word_count_result);
	if (!res)
		return (NULL);
	data.res = res;
	data.j = &j;
	data.s_word = &s_word;
	data.delimiters = delimiters;
	data.s = s;
	initialize_vars(&j, &s_word);
	handle_split_logic(&data);
	return (res);
}

char	**ft_split2(const char *s, const char *delimiters)
{
	if (!s || !delimiters)
		return (NULL);
	return (setup_split(s, delimiters));
}
