/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 22:47:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/06 15:26:24 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libprintf/libprintf.h"

void			fmt(t_ent **ents, size_t n, size_t maxlen)
{
	size_t		i;

	(void)maxlen;
	i = 0;
	while (i < n)
	{
		if (!ents[i]->ignore)
			FMT("%s%c", ents[i]->name, i + 1 == n ? '\n' : ' ');
		i++;
	}
}
