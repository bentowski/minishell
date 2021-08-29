/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:30:16 by bbaudry           #+#    #+#             */
/*   Updated: 2021/08/29 20:50:19 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

// static t_error ft_error(t_error errors[])
// {
// 	errors = [{UKN_ERR, "Unknown error." }];
// 	// {NB_ARG, "Invalid call: Incorrect number of arguments." },
// 	// {FILE_FRMT, "Invalid file: Use the '.ber' extension." },
// 	// {READ_ERR, "Invalid file: cannot read input file." },
// 	// {CLOSEMAP_ERR, "Invalid map: unclosed." },
// 	// {MAP_CFG, "Invalid map: no regular map" },
// 	// {BADCHAR_ERR, "Invalid map: unexpected character detected" },
// 	// {NOE_ERR, "Invalid map: no or multiple exit(s) detected" },
// 	// {NOP_ERR, "Invalid map: no or multiple player(s) detected" },
// 	// {NOC_ERR, "Invalid map: no collectors detected" },
// 	// {MEM_ERR, "Memory allocation failed while parsing shapes." }
//     return (*errors);
// }

static	char	*get_error_msg(t_err raised)
{
    t_error *errors;

    // errors = ft_error(errors);
    errors = malloc(sizeof(t_error) * 1);
    if (!errors)
        return ((char *)strerror(errno));
    errors[0] = {UKN_ERR, "Unknown error." };
	if (raised != ERRNO_TO_STR)
		return (errors[raised].msg);
	return ((char *)strerror(errno));
}

void	error(t_err raised, char *line, char **map)
{
	char	*msg;

	if (line)
		free(line);
	if (map)
		ft_free(map);
	msg = get_error_msg(raised);
	printf("Error\n%d: %s\n", raised, msg);
	exit(EXIT_FAILURE);
}
