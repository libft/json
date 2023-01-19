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
#include "test.h"

static t_err	read_file_contents(const char *filename, char **out)
{
	FILE *const		fp = fopen(filename, "rb");
	unsigned long	length;
	bool			error;

	length = 0;
	error = !fp;
	*out = NULL;
	if (!error && fseek(fp, 0, SEEK_END))
		error = true;
	if (!error)
		length = ftell(fp);
	if (!error && fseek(fp, 0, SEEK_SET))
		error = true;
	if (!error)
		*out = malloc(length + 1);
	if (!*out)
		error = true;
	if (!error && fread(*out, 1, length, fp) != length)
		error = true;
	if (fp)
		fclose(fp);
	if (error)
		free(*out);
	(*out)[length] = '\0';
	return (error);
}

static bool	test_leak(const void *context)
{
	const char *const			str = context;
	t_ft_json_value_internal	result;
	volatile int *volatile		prevent_failure;

	leak_test_start();
	prevent_failure = malloc(sizeof(int));
	if (prevent_failure)
		*((volatile int *)prevent_failure) = 42;
	free((void *)prevent_failure);
	if (!ft_json_parse_internal(str, &result))
		ft_json_free_value(&result);
	return (false);
}

int	main(int argc, char **argv)
{
	char						*str;
	t_ft_json_value_internal	result;
	t_err						error;
	int							errno;

	if (argc < 2
		|| read_file_contents(argv[1], &str)
		|| ft_json_parse_internal(str, &result))
		return (EXIT_FAILURE);
	if (result.type == FT_JSON_VALUE_TYPE_ERROR)
		error = puts("Invalid JSON") < 0;
	else
		error = print_tree(result, 0);
	ft_json_free_value(&result);
	if (error)
		return (EXIT_FAILURE);
	errno = leak_test(test_leak, str, NULL);
	error = !!errno;
	if (error)
	{
		printf("leak_test: %s\n", leak_test_error(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
