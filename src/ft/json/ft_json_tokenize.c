/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_file_name (file name is useless too)          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42header-remover <whatever@example.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by file history     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_json_internal.h"

#include <stddef.h>

static const t_ft_json_tokenizer_state	g_state[] = {
	NULL,
};

t_err	ft_json_tokenize(const char *str, t_ft_json_token_list *out)
{
	int						current_state;
	void					*data;
	t_ft_json_token_list	result;

	result.head = NULL;
	result.tail = NULL;
	current_state = FT_JSON_TOKENIZER_STATE_ACCEPT_VALUE;
	data = NULL;
	str--;
	while (*++str)
	{
		if (current_state == FT_JSON_TOKENIZER_STATE_ERROR
			|| g_state[current_state](&current_state, &result, data))
		{
			// TODO: free resources
			return (true);
		}
	}
	if (current_state != FT_JSON_TOKENIZER_STATE_DONE)
	{
		// TODO: free resources
		return (true);
	}
	*out = result;
	return (false);
}
