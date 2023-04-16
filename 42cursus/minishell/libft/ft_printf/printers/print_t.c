/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:40 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_t(t_pflags *tf)
{	
	char	*code;

	code = INF;
	if (tf->length != 0)
		tf->dimension--;
	if (tf->length == 1)
		code = ERR;
	else if (tf->length == 2)
		code = SIG;
	else if (tf->length == 3)
		code = WAR;
	write(1, code, pf_strlen(code));
	tf->dimension += pf_strlen(code);
}
