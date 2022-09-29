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

#include <stdio.h>
#include <stdlib.h>

char	*read_file_contents(const char *filename)
{
	FILE *const		fp = fopen(filename, "rb");
	unsigned long	length;
	char			*str;

	if (!fp)
		return (NULL);
	if (fseek(fp, 0, SEEK_END))
		return (NULL);
	length = ftell(fp);
	if (fseek(fp, 0, SEEK_SET))
		return (NULL);
	str = malloc(length + 1);
	if (!str)
		return (NULL);
	if (fread(str, 1, length, fp) != length)
		return (NULL);
	fclose(fp);
	str[length] = '\0';
	return (str);
}

t_err	print_token_normal(t_ft_json_token *token)
{
	if (*token->type == FT_JSON_TOKEN_TYPE_NUMBER)
		return (printf("NUMBER - %lf\n", token->number->value) < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_STRING)
		return (printf("STRING - %s\n", token->string->value) < 0);
	return (true);
}

t_err	print_token_special(t_ft_json_token *token)
{
	if (*token->type == FT_JSON_TOKEN_TYPE_EOF)
		return (puts("EOF") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_NULL)
		return (puts("NULL") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_COMMA)
		return (puts("COMMA") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_COLON)
		return (puts("COLON") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_TRUE)
		return (puts("TRUE") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_FALSE)
		return (puts("FALSE") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_BRACE_OPEN)
		return (puts("BRACE_OPEN") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_BRACE_CLOSE)
		return (puts("BRACE_CLOSE") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_BRACKET_OPEN)
		return (puts("BRACKET_OPEN") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_BRACKET_CLOSE)
		return (puts("BRACKET_CLOSE") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_NUMBER)
		return (puts("NUMBER") < 0);
	if (*token->type == FT_JSON_TOKEN_TYPE_STRING)
		return (puts("STRING") < 0);
	return (true);
}

t_err	print_token_list(t_ft_json_token_list list)
{
	t_ft_json_token_list_node	*node;

	if (!list.head)
		return (puts("Invalid token") < 0);
	node = list.head;
	while (node)
	{
		if (*node->value.type == FT_JSON_TOKEN_TYPE_NUMBER
			|| *node->value.type == FT_JSON_TOKEN_TYPE_STRING)
		{
			if (print_token_normal(&node->value))
				return (true);
		}
		else
		{
			if (print_token_normal(&node->value))
				return (true);
		}
		node = node->next;
	}
	return (false);
}

int	main(int argc, char **argv)
{
	char					*str;
	t_ft_json_token_list	list;

	if (argc < 2)
		return (EXIT_FAILURE);
	str = read_file_contents(argv[1]);
	if (!str)
		return (EXIT_FAILURE);
	if (ft_json_tokenize(str, &list))
		return (EXIT_FAILURE);
	if (print_token_list(list))
	{
		ft_json_token_list_free(list);
		return (EXIT_FAILURE);
	}
	ft_json_token_list_free(list);
	return (EXIT_SUCCESS);
}
