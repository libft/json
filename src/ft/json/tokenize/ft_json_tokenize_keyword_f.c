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

t_err	ft_json_tokenize_keyword_f(
	char c,
	t_ft_json_token_list *list,
	void *data,
	t_ft_json_tokenizer_state *next_state
)
{
	(void)list;
	(void)data;
	if (c == 'a')
		next_state->state = FT_JSON_TOKENIZER_STATE_KEYWORD_FA;
	else
		next_state->state = FT_JSON_TOKENIZER_STATE_ERROR;
	return (false);
}
