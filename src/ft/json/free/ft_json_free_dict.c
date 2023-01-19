/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_free_dict.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/01/19 23:52:21 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_json_internal.h"

#include <stdlib.h>

void	ft_json_free_dict(
	t_ft_json_value_dict *value
)
{
	t_ft_json_dict_node	*node;

	while (value->value.head)
	{
		node = value->value.head;
		value->value.head = node->next;
		free(node->key);
		ft_json_free_value(node->value);
		free(node->value);
		free(node);
	}
}
