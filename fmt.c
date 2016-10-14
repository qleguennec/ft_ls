/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/06 22:47:48 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/08 05:43:51 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libprintf/libprintf.h"

void			fmt(t_ent **ents, size_t n, size_t maxlen)
{
	size_t		i;
	size_t		total;

	i = 0;
	total = 0;
	while (i < n)
	{
		vect_fmt(&g_m_buf, "%-*s", i + 1 == n ? 0 : maxlen, ents[i]->name);
		total += maxlen;
		if (i + 1 == n)
			vect_mset_end(&g_m_buf, '\n', 1);
		else if (total + maxlen > (size_t)g_ncols)
		{
			total = 0;
			vect_mset_end(&g_m_buf, '\n', 1);
		}
		else
		{
			total++;
			vect_mset_end(&g_m_buf, ' ', 1);
		}
		i++;
		FLUSH;
	}
}
