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

#include "test.h"

#include <stdio.h>

static t_err	print_string(t_ft_json_value_string value, int depth)
{
	char	*str;

	if (printf("%*sstring: ", depth, "") < 0)
		return (true);
	str = value.value - 1;
	while (*++str)
	{
		if (*str == '\n' && printf("\n") < 0)
			return (true);
		if (*str != '\n' && printf("%c", *str) < 0)
			return (true);
	}
	if (printf("\n") < 0)
		return (true);
	return (false);
}

static t_err	print_special(t_ft_json_value_internal value, int depth)
{
	if (value.type == FT_JSON_VALUE_TYPE_NULL)
		return (printf("%*snull\n", depth, "") < 0);
	if (value.type == FT_JSON_VALUE_TYPE_BOOLEAN && value.boolean.value)
		return (printf("%*sboolean: true\n", depth, "") < 0);
	if (value.type == FT_JSON_VALUE_TYPE_BOOLEAN && !value.boolean.value)
		return (printf("%*sboolean: false\n", depth, "") < 0);
	if (value.type == FT_JSON_VALUE_TYPE_NUMBER)
		return (printf("%*snumber: %lf\n", depth, "", value.number.value) < 0);
	if (value.type == FT_JSON_VALUE_TYPE_STRING)
		return (print_string(value.string, depth));
	return (true);
}

static t_err	print_list(t_ft_json_value_list value, int depth)
{
	t_ft_json_list_node	*node;

	if (printf("%*slist\n", depth, "") < 0)
		return (true);
	node = value.value.head;
	while (node)
	{
		if (print_tree(*node->value, depth + 1))
			return (true);
		node = node->next;
	}
	return (false);
}

static t_err	print_dict(t_ft_json_value_dict value, int depth)
{
	t_ft_json_dict_node	*node;

	if (printf("%*sdict\n", depth, "") < 0)
		return (true);
	node = value.value.head;
	while (node)
	{
		if (false
			|| printf("%*sentry\n", depth + 1, "") < 0
			|| printf("%*skey: %s\n", depth + 2, "", node->key) < 0
			|| print_tree(*node->value, depth + 2))
			return (true);
		node = node->next;
	}
	return (false);
}

t_err	print_tree(t_ft_json_value_internal value, int depth)
{
	if (value.type == FT_JSON_VALUE_TYPE_LIST)
		return (print_list(value.list, depth));
	if (value.type == FT_JSON_VALUE_TYPE_DICT)
		return (print_dict(value.dict, depth));
	return (print_special(value, depth));
}
