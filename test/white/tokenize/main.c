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

#include "ft/leak_test.h"

static const char *const	g_token_name[] = {
	"EOF",
	"NULL",
	"COMMA",
	"COLON",
	"TRUE",
	"FALSE",
	"BRACE_OPEN",
	"BRACE_CLOSE",
	"BRACKET_OPEN",
	"BRACKET_CLOSE",
};

static char	*read_file_contents(const char *filename)
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

static t_err	print_token_list(t_ft_json_token_list list)
{
	t_ft_json_token_list_node	*node;

	if (!list.head)
		return (puts("Invalid token") < 0);
	node = list.head;
	while (node)
	{
		if (*node->value.type == FT_JSON_TOKEN_TYPE_NUMBER)
		{
			if (printf("NUMBER - %lf\n", node->value.number->value) < 0)
				return (true);
		}
		else if (*node->value.type == FT_JSON_TOKEN_TYPE_STRING)
		{
			if (printf("STRING - %s\n", node->value.string->value) < 0)
				return (true);
		}
		else
		{
			if (puts(g_token_name[*node->value.type]) < 0)
				return (true);
		}
		node = node->next;
	}
	return (false);
}

static bool	test_leak(const void *context)
{
	const char *const		str = context;
	t_ft_json_token_list	list;

	leak_test_start();
	if (ft_json_tokenize(str, &list))
		return (false);
	ft_json_token_list_free(list);
	leak_test_end();
	return (false);
}

int	main(int argc, char **argv)
{
	char					*str;
	t_ft_json_token_list	list;
	int						errno;

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
	errno = leak_test(test_leak, str, NULL);
	if (errno)
	{
		printf("leak_test error: %s\n", leak_test_error(errno));
		return (EXIT_FAILURE);
	}
	ft_json_token_list_free(list);
	return (EXIT_SUCCESS);
}
