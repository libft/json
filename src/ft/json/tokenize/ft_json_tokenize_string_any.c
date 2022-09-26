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
#include "ft_types_char.h"

typedef t_ft_json_tokenizer_state	t_s;
typedef t_ft_json_token_string		t_v;

static void	free_value(t_ft_json_token value)
{
	free(value.string->value);
	free(value.string);
}

static t_err	add_token(
	t_ft_json_token_list *list,
	t_ft_json_tokenizer_state_string *state
)
{
	char *const							string
		= stringbuilder_to_string(state->stringbuilder, 0);
	t_ft_json_token_string *const		token
		= malloc(sizeof(t_ft_json_token_string));
	t_ft_json_token_list_node *const	node
		= malloc(sizeof(t_ft_json_token_list_node));

	stringbuilder_free(state->stringbuilder);
	if (!string || !token || !node)
	{
		free(string);
		free(token);
		free(node);
		return (true);
	}
	*token = (t_v){FT_JSON_TOKEN_TYPE_STRING, string};
	node->next = NULL;
	node->free_value = free_value;
	node->value.string = token;
	if (list->head)
		list->tail->next = node;
	else
		list->head = node;
	list->tail = node;
	return (false);
}

t_err	ft_json_tokenize_string_any(
	char c,
	t_ft_json_token_list *list,
	void *data,
	t_ft_json_tokenizer_state *next_state
)
{
	if (c == '"')
	{
		*next_state = (t_s){FT_JSON_TOKENIZER_STATE_DEFAULT, NULL};
		return (add_token(list, (t_ft_json_tokenizer_state_string *)data));
	}
	else if (c == '\\')
	{
		*next_state = (t_s){FT_JSON_TOKENIZER_STATE_STRING_BACKSLASH, data};
		return (add_token(list, (t_ft_json_tokenizer_state_string *)data));
	}
	else if (ft_types_char_cntrl(c))
	{
		*next_state = (t_s){FT_JSON_TOKENIZER_STATE_ERROR, NULL};
		return (false);
	}
	*next_state = (t_s){FT_JSON_TOKENIZER_STATE_STRING_BACKSLASH, data};
	if (stringbuilder_append_char(
			((t_ft_json_tokenizer_state_string *)data)->stringbuilder, c))
	{
		stringbuilder_free(
			((t_ft_json_tokenizer_state_string *)data)->stringbuilder);
		free(data);
		return (true);
	}
	return (false);
}
