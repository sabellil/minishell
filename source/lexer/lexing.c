/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabellil <sabellil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 17:41:25 by mairivie          #+#    #+#             */
/*   Updated: 2025/03/23 14:34:43 by sabellil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/init_shell.h"

t_token	*tokenize_line(char *line)
{
	int		i;
	t_token	*head_of_list;
	t_token	*new_token;

	i = 0;
	head_of_list = NULL;
	while (line[i])
	{
		if (ft_is_whitespace(line[i]) == true)
			i++;
		else
		{
			new_token = create_token(line, i, NULL);
			if (new_token == NULL)
			{
				free_token_list(&head_of_list);
				return (NULL);
			}
			ft_tokadd_back(&head_of_list, new_token);
			i += ft_strlen(new_token->content) - (new_token->quote_added * 2);
		}
	}
	return (head_of_list);
}

int	null_exit_code(t_data *data, int exit_code)
{
	if (data)
	{
		data->lst_exit = exit_code;
		update_exit_status(data, exit_code);
	}
	return (FAILURE);
}

t_token	*lexer( t_data *data, char *line)
{
	t_token	*head_of_list;

	head_of_list = tokenize_line(line);
	if (!head_of_list)
		null_exit_code(data, 2);
	if (!head_of_list)
		return (NULL);
	if (check_lexing(head_of_list) == FAILURE)
	{
		ft_printf("bash: Syntax error \n");
		free_token_list(&head_of_list);
		return (null_exit_code(data, 2), NULL);
	}
	return (head_of_list);
}
