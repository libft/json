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

static const t_ft_json_tokenizer_state_function	g_state_functions[] = {
	ft_json_tokenize_default,
};

t_err	ft_json_tokenize(
	const char *str,
	t_ft_json_token_list *out
)
{
	t_ft_json_tokenizer_state	current_state;
	t_ft_json_token_list		result;
	size_t						i;
	t_err						error;

	error = false;
	current_state.state = FT_JSON_TOKENIZER_STATE_DEFAULT;
	current_state.data = NULL;
	result.head = NULL;
	result.tail = NULL;
	*out = result;
	i = -1;
	while (!error && (i++ == (size_t)-1 || str[i - 1]))
		if (current_state.state == FT_JSON_TOKENIZER_STATE_ERROR
			|| g_state_functions[current_state.state](
			*str, &result, current_state.data, &current_state))
			error = true;
	if (current_state.state != FT_JSON_TOKENIZER_STATE_DEFAULT)
		return (false);
	if (error)
		ft_json_token_list_free(result);
	else
		*out = result;
	return (error);
}
