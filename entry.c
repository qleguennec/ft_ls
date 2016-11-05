/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 23:17:25 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/05 16:44:51 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "malloc.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include <errno.h>

t_ent		*entry(char *fn, t_cat *cat)
{
	t_ent	*ret;
	char	*s;

	MALLOC_SIZEOF(ret);
	ret->name = ft_strdup(fn);
	if (cat)
	{
		ft_strcpy(cat->p, fn);
		s = cat->name;
	}
	else
		s = fn;
	if ((ret->ignore = stat(s, &ret->st) == -1))
		WARN(g_access_warn, ret->name);
	return (ret);
}
