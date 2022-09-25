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

t_err	ft_json_tokenizer_state_string(
	void **to
)
{
	t_ft_json_tokenizer_state_string *const	result
		= malloc(sizeof(t_ft_json_tokenizer_state_string));
	t_stringbuilder *const					stringbuilder
		= new_stringbuilder(1024);

	if (!result || !stringbuilder)
	{
		free(result);
		if (stringbuilder)
			stringbuilder_free(stringbuilder);
		return (true);
	}
	result->stringbuilder = stringbuilder;
	*to = result;
	return (false);
}
