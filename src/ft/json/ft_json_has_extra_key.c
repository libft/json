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

#include "ft_json.h"

#include "ft_json_internal.h"

static inline bool	ft_cstring_equals(const char *a, const char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return (!*a && !*b);
}

static inline bool	array_has(
	const char *const *keys,
	size_t count,
	const char *string
)
{
	size_t	i;

	i = -1;
	while (++i < count)
		if (ft_cstring_equals(keys[i], string))
			return (true);
	return (false);
}

bool	ft_json_has_extra_key(
	t_ft_json value,
	const char *const *keys,
	size_t count
)
{
	t_ft_json_value_internal *const	self = value;
	t_ft_json_dict_node				*current;

	current = self->dict.value.head;
	while (current)
	{
		if (array_has(keys, count, current->key))
			return (true);
		current = current->next;
	}
	return (false);
}
