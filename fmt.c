/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 22:47:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/06 22:52:30 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libprintf/libprintf.h"

void			fmt(t_ent **ents, size_t n)
{
	size_t		i;

	i = -1;
	while (++i < n)
	{
		vect_fmt(&g_m_buf, "%s%c", ents[i]->name, i + 1 == n ? '\n' : ' ');
		FLUSH;
	}
}
