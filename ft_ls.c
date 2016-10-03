/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 19:12:28 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/03 20:03:21 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libprintf/libprintf.h"
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int				ft_ls(char *fn, t_opts opts)
{
	int			ret;
	t_stat		st;

	ret = stat(fn, &st);
	(void)opts;
	if (ret == -1)
		ft_dprintf(2, "ls: cannot access '%s': %s\n", fn, strerror(errno));
	return (0);
}
