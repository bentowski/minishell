/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 22:25:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/27 19:05:09 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# include <errno.h>
# include <string.h>
# include "../minishell.h"

typedef enum e_err
{
	ERRNO_TO_STR = -1,
	UKN_ERR,
	MEM_ERR,
	QUOTE_ERR,
	BAD_FILE
	// NB_ARG,
	// FILE_FRMT,
	// READ_ERR,
	// CLOSEMAP_ERR,
	// MAP_CFG,
	// BADCHAR_ERR,
	// NOE_ERR,
	// NOP_ERR,
	// NOC_ERR,
}		t_err;

typedef struct s_error
{
	t_err	u_id;
	char	*msg;
}		t_error;

int	error(t_err raised, t_struct lst, char *line, int critical);

#endif
