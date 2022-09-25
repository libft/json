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

t_err	ft_json_tokenize_default(
	char c,
	int *next_state,
	t_ft_json_token_list *list,
	void **data
)
{
	*next_state = FT_JSON_TOKENIZER_STATE_ERROR;
	if (c == '[' || c == ']' || c == '{' || c == '}' || c == ':' || c == ',')
	{
		*next_state = FT_JSON_TOKENIZER_STATE_DEFAULT;
		return ((c == '[' && add_token(list, FT_JSON_TOKEN_TYPE_BRACKET_OPEN))
			|| (c == ']' && add_token(list, FT_JSON_TOKEN_TYPE_BRACKET_CLOSE))
			|| (c == '{' && add_token(list, FT_JSON_TOKEN_TYPE_BRACE_OPEN))
			|| (c == '}' && add_token(list, FT_JSON_TOKEN_TYPE_BRACE_CLOSE))
			|| (c == ':' && add_token(list, FT_JSON_TOKEN_TYPE_COLON))
			|| (c == ',' && add_token(list, FT_JSON_TOKEN_TYPE_COMMA)));
	}
	else if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
		*next_state = FT_JSON_TOKENIZER_STATE_DEFAULT;
	else if (c == '-' || ('0' <= c && c <= '9'))
	{
		*next_state = FT_JSON_TOKENIZER_STATE_NUMBER;
		return (ft_json_tokenizer_state_number(data, c));
	}
	else if (c == '"')
	{
		*next_state = FT_JSON_TOKENIZER_STATE_STRING;
		return (ft_json_tokenizer_state_string(data));
	}
	return (false);
}
