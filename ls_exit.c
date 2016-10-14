/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:57:38 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/08 04:10:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf/libprintf.h"
#include <stdlib.h>
#include <stdarg.h>

void		ls_exit(int ret, const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	ft_dprintf(2, "ls: ");
	ft_vdprintf(2, format, ap);
	ft_dprintf(2, "\n");
	exit(ret);
}
