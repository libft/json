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

#ifndef FT_JSON_INTERNAL_H
# define FT_JSON_INTERNAL_H

# include "ft_json.h"

typedef enum e_ft_json_token_type
{
	FT_JSON_TOKEN_TYPE_NULL,
	FT_JSON_TOKEN_TYPE_COMMA,
	FT_JSON_TOKEN_TYPE_COLON,
	FT_JSON_TOKEN_TYPE_TRUE,
	FT_JSON_TOKEN_TYPE_FALSE,
	FT_JSON_TOKEN_TYPE_BRACE_OPEN,
	FT_JSON_TOKEN_TYPE_BRACE_CLOSE,
	FT_JSON_TOKEN_TYPE_BRACKET_OPEN,
	FT_JSON_TOKEN_TYPE_BRACKET_CLOSE,
	FT_JSON_TOKEN_TYPE_NUMBER,
	FT_JSON_TOKEN_TYPE_STRING,
}	t_ft_json_token_type;

typedef struct s_ft_json_token_number
{
	t_ft_json_token_type	type;
	double					value;
}	t_ft_json_token_number;

typedef struct s_ft_json_token_string
{
	t_ft_json_token_type	type;
	char					*value;
}	t_ft_json_token_string;

typedef union u_ft_json_token
{
	t_ft_json_token_type	*type;
	t_ft_json_token_number	*number;
	t_ft_json_token_string	*string;
}	t_ft_json_token;

typedef struct s_ft_json_token_list_node
{
	struct s_ft_json_token_list_node	*next;
	t_ft_json_token						value;
}	t_ft_json_token_list_node;

typedef struct s_ft_json_token_list
{
	t_ft_json_token_list_node	*head;
	t_ft_json_token_list_node	*tail;
}	t_ft_json_token_list;

# define FT_JSON_TOKENIZER_STATE_ERROR -1
# define FT_JSON_TOKENIZER_STATE_DEFAULT 0
# define FT_JSON_TOKENIZER_STATE_QUOTE 1
# define FT_JSON_TOKENIZER_STATE_NUMBER 2
# define FT_JSON_TOKENIZER_STATE_WORD 3

typedef t_err	(*t_ft_json_tokenizer_state)(
					char c,
					int *next_state,
					t_ft_json_token_list *list,
					void **data);

t_err	ft_json_tokenize(const char *str, t_ft_json_token_list *out);

t_err	ft_json_tokenize_default(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);
t_err	ft_json_tokenize_quote(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);
t_err	ft_json_tokenize_number(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);
t_err	ft_json_tokenize_word(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);

#endif
