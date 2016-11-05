/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_mtim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 23:22:44 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/03 14:47:14 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"

int			sort_mtim(void *a, void *b)
{
	t_ent			*e_a;
	t_ent			*e_b;
	unsigned long	t_a;
	unsigned long	t_b;

	e_a = a;
	e_b = b;
	t_a = e_a->st.st_mtimespec.tv_sec;
	t_b = e_b->st.st_mtimespec.tv_sec;
	if (t_a != t_b)
		return (t_b - t_a);
	else
		return (STRCMP(e_a->name, e_b->name));
}
