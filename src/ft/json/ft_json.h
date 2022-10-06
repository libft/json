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

#ifndef FT_JSON_H
# define FT_JSON_H

# include <stdbool.h>

# include "ft_types.h"

typedef enum e_ft_json_value_type
{
	FT_JSON_VALUE_TYPE_ERROR,
	FT_JSON_VALUE_TYPE_NULL,
	FT_JSON_VALUE_TYPE_BOOLEAN,
	FT_JSON_VALUE_TYPE_NUMBER,
	FT_JSON_VALUE_TYPE_STRING,
	FT_JSON_VALUE_TYPE_LIST,
	FT_JSON_VALUE_TYPE_DICT,
}	t_ft_json_value_type;

typedef struct s_ft_json_list_node
{
	struct s_ft_json_list_node		*next;
	union u_ft_json_value_internal	*value;
}	t_ft_json_list_node;

typedef struct s_ft_json_list
{
	t_ft_json_list_node	*head;
	t_ft_json_list_node	*tail;
}	t_ft_json_list;

typedef struct s_ft_json_value_boolean
{
	t_ft_json_value_type	type;
	bool					value;
}	t_ft_json_value_boolean;

typedef struct s_ft_json_value_number
{
	t_ft_json_value_type	type;
	double					value;
}	t_ft_json_value_number;

typedef struct s_ft_json_value_string
{
	t_ft_json_value_type	type;
	char					*value;
}	t_ft_json_value_string;

typedef struct s_ft_json_value_list
{
	t_ft_json_value_type	type;
	t_ft_json_list			value;
}	t_ft_json_value_list;

t_err	ft_json_parse(const char *str, void **out);
t_err	ft_json_stringify(const void *value, char *out);

#endif
