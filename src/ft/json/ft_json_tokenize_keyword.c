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
#include <stdint.h>

static const char	g_expected[] = {
	'r',
	'u',
	'e',
	'a',
	'l',
	's',
	'e',
	'u',
	'l',
	'l',
};

static t_err	add_token(t_ft_json_token_list *list, t_ft_json_token_type type)
{
	t_ft_json_token_type *const			token
		= malloc(sizeof(t_ft_json_token_type));
	t_ft_json_token_list_node *const	node
		= malloc(sizeof(t_ft_json_token_list_node));

	if (!token || !node)
	{
		free(token);
		free(node);
		return (true);
	}
	*token = type;
	node->next = NULL;
	node->free_value = (void (*)(t_ft_json_token))free;
	node->value.type = token;
	if (list->head)
		list->tail->next = node;
	else
		list->head = node;
	list->tail = node;
	return (false);
}

t_err	ft_json_tokenize_keyword(
	char c,
	int *next_state,
	t_ft_json_token_list *list,
	void **data
)
{
	uintptr_t	real_data;

	real_data = *((uintptr_t *)*data);
	if (c != g_expected[real_data])
	{
		*data = NULL;
		*next_state = FT_JSON_TOKENIZER_STATE_ERROR;
	}
	real_data++;
	if (real_data == 3 && add_token(list, FT_JSON_TOKEN_TYPE_TRUE))
		return (true);
	if (real_data == 7 && add_token(list, FT_JSON_TOKEN_TYPE_FALSE))
		return (true);
	if (real_data == 10 && add_token(list, FT_JSON_TOKEN_TYPE_NULL))
		return (true);
	*((uintptr_t *)data) = real_data;
	*next_state = FT_JSON_TOKENIZER_STATE_KEYWORD;
	if (real_data == 3 || real_data == 7 || real_data == 10)
	{
		*data = NULL;
		*next_state = FT_JSON_TOKENIZER_STATE_DEFAULT;
	}
	return (false);
}
