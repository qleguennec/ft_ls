/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 23:22:44 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/05 19:29:56 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"

int			sort_time(void *a, void *b)
{
	t_ent			*e_a;
	t_ent			*e_b;
	unsigned long	t_a;
	unsigned long	t_b;

	e_a = a;
	e_b = b;
	t_a = entry_gettime(e_a);
	t_b = entry_gettime(e_b);
	if (t_a != t_b)
		return (t_b - t_a);
	else
		return (STRCMP(e_a->name, e_b->name));
}
