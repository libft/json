/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_free_value.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 2023/01/19 23:51:12 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_json_internal.h"

void	ft_json_free_value(
	t_ft_json_value_internal *value
)
{
	if (value->type == FT_JSON_VALUE_TYPE_STRING)
		ft_json_free_string(&value->string);
	else if (value->type == FT_JSON_VALUE_TYPE_LIST)
		ft_json_free_list(&value->list);
	else if (value->type == FT_JSON_VALUE_TYPE_DICT)
		ft_json_free_dict(&value->dict);
}
