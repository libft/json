/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_tokenize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2022/09/24 00:00:53 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_json_internal.h"

#include <stddef.h>

static const t_ft_json_tokenizer_state	g_state[] = {
	ft_json_tokenize_default,
	ft_json_tokenize_string,
	ft_json_tokenize_number,
	ft_json_tokenize_keyword,
};

t_err	ft_json_tokenize(const char *str, t_ft_json_token_list *out)
{
	int						current_state;
	void					*data;
	t_ft_json_token_list	result;

	result.head = NULL;
	result.tail = NULL;
	current_state = FT_JSON_TOKENIZER_STATE_DEFAULT;
	data = NULL;
	str--;
	while (*++str)
	{
		if (current_state == FT_JSON_TOKENIZER_STATE_ERROR
			|| g_state[current_state](*str, &current_state, &result, &data))
		{
			// TODO: free resources
			return (true);
		}
	}
	if (current_state != FT_JSON_TOKENIZER_STATE_DEFAULT)
	{
		// TODO: free resources
		return (true);
	}
	*out = result;
	return (false);
}
