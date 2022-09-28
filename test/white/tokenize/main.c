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
	return (EXIT_SUCCESS);
}
