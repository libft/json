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

#include <stdlib.h>

#include "ft_stringbuilder.h"

t_err	ft_json_tokenizer_state_number(
	void **to,
	char c
)
{
	t_ft_json_tokenizer_state_number *const	result
		= malloc(sizeof(t_ft_json_tokenizer_state_number));

	if (!result)
		return (true);
	result->current_digit = 1;
	result->value = 0;
	result->sign = 1;
	result->state = FT_JSON_TOKENIZER_STATE_NUMBER_INTEGER;
	if (c == '-')
	{
		result->sign = -1;
		result->state = FT_JSON_TOKENIZER_STATE_NUMBER_MINUS;
	}
	else if (c == '0')
		result->state = FT_JSON_TOKENIZER_STATE_NUMBER_ZERO;
	else
		result->value = c - '0';
	*to = result;
	return (false);
}
