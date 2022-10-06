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

t_err	ft_strdup(const char *src, char **out)
{
	size_t		length;
	char		*result;
	const char	*tmp;
	char		*temp;

	length = 0;
	tmp = src;
	while (*tmp)
	{
		tmp++;
		length++;
	}
	result = malloc(length + 1);
	if (!result)
		return (true);
	tmp = src;
	temp = result;
	while (*src)
		*temp++ = *tmp++;
	*temp = '\0';
	*out = result;
	return (false);
}

static t_err	special(
	t_ft_json_token_list_node *head,
	t_ft_json_token_list_node *out_next_head,
	t_ft_json_value_internal *out
)
{
	*out_next_head = *head->next;
	if (*head->value.type == FT_JSON_TOKEN_TYPE_NULL)
		out->type = FT_JSON_VALUE_TYPE_NULL;
	if (*head->value.type == FT_JSON_TOKEN_TYPE_TRUE
		|| *head->value.type == FT_JSON_TOKEN_TYPE_FALSE)
	{
		out->type = FT_JSON_VALUE_TYPE_BOOLEAN;
		out->boolean.value = *head->value.type == FT_JSON_TOKEN_TYPE_TRUE;
	}
	if (*head->value.type == FT_JSON_TOKEN_TYPE_NUMBER)
	{
		out->type = FT_JSON_VALUE_TYPE_NUMBER;
		out->number.value = head->value.number->value;
	}
	if (*head->value.type == FT_JSON_TOKEN_TYPE_STRING)
	{
		out->type = FT_JSON_VALUE_TYPE_STRING;
		return (ft_strdup(head->value.string->value, &out->string.value));
	}
	return (false);
}

t_err	ft_json_parse_value(
	t_ft_json_token_list_node *head,
	t_ft_json_token_list_node *out_next_head,
	t_ft_json_value_internal *out
)
{
	if (*head->value.type == FT_JSON_TOKEN_TYPE_NULL
		|| *head->value.type == FT_JSON_TOKEN_TYPE_TRUE
		|| *head->value.type == FT_JSON_TOKEN_TYPE_FALSE
		|| *head->value.type == FT_JSON_TOKEN_TYPE_NUMBER
		|| *head->value.type == FT_JSON_TOKEN_TYPE_STRING)
		return (special(head, out_next_head, out));
	if (*head->value.type == FT_JSON_TOKEN_TYPE_BRACE_OPEN)
		return (ft_json_parse_dict(head, out_next_head, &out->dict));
	if (*head->value.type == FT_JSON_TOKEN_TYPE_BRACKET_OPEN)
		return (ft_json_parse_list(head, out_next_head, &out->list));
	out->type = FT_JSON_VALUE_TYPE_ERROR;
	return (false);
}
