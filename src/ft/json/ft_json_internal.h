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

# include "ft_stringbuilder.h"

typedef enum e_ft_json_token_type
{
	FT_JSON_TOKEN_TYPE_EOF,
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
	void								(*free_value)(t_ft_json_token);
	t_ft_json_token						value;
}	t_ft_json_token_list_node;

typedef struct s_ft_json_token_list
{
	t_ft_json_token_list_node	*head;
	t_ft_json_token_list_node	*tail;
}	t_ft_json_token_list;

# define FT_JSON_TOKENIZER_STATE_ERROR -1
# define FT_JSON_TOKENIZER_STATE_DEFAULT 0
# define FT_JSON_TOKENIZER_STATE_STRING 1
# define FT_JSON_TOKENIZER_STATE_NUMBER 2
# define FT_JSON_TOKENIZER_STATE_KEYWORD 3

typedef t_err	(*t_ft_json_tokenizer_state)(
					char c,
					int *next_state,
					t_ft_json_token_list *list,
					void **data);
t_err	ft_json_tokenize(
			const char *str,
			t_ft_json_token_list *out);
void	ft_json_token_list_free(
			t_ft_json_token_list list);
t_err	ft_json_tokenize_default(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);
t_err	ft_json_tokenize_string(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);
t_err	ft_json_tokenize_number(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);
t_err	ft_json_tokenize_keyword(
			char c,
			int *next_state,
			t_ft_json_token_list *list,
			void **data);

typedef enum e_ft_json_tokenizer_state_string_escape
{
	FT_JSON_TOKENIZER_STATE_STRING_NORMAL,
	FT_JSON_TOKENIZER_STATE_STRING_BACKSLASH,
	FT_JSON_TOKENIZER_STATE_STRING_X,
	FT_JSON_TOKENIZER_STATE_STRING_X2,
}	t_ft_json_tokenizer_state_string_escape;

typedef struct s_ft_json_tokenizer_state_string
{
	t_stringbuilder							*stringbuilder;
	t_ft_json_tokenizer_state_string_escape	escape;
	unsigned char							x;
}	t_ft_json_tokenizer_state_string;

t_err	ft_json_tokenizer_state_string(
			void **to);

typedef enum e_ft_json_tokenizer_state_number_part
{
	FT_JSON_TOKENIZER_STATE_NUMBER_MINUS,
	FT_JSON_TOKENIZER_STATE_NUMBER_ZERO,
	FT_JSON_TOKENIZER_STATE_NUMBER_INTEGER,
	FT_JSON_TOKENIZER_STATE_NUMBER_DOT,
	FT_JSON_TOKENIZER_STATE_NUMBER_FRACTION,
	FT_JSON_TOKENIZER_STATE_NUMBER_E,
	FT_JSON_TOKENIZER_STATE_NUMBER_EXPONENT,
}	t_ft_json_tokenizer_state_number_part;

typedef struct s_ft_json_tokenizer_state_number
{
	double									value;
	double									current_digit;
	t_ft_json_tokenizer_state_number_part	state;
	int										sign;
}	t_ft_json_tokenizer_state_number;

t_err	ft_json_tokenizer_state_number(
			void **to,
			char c);

#endif
