/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_mtim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 23:22:44 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/07 23:30:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"

int			sort_mtim(void *a, void *b)
{
	t_ent	*e_a;
	t_ent	*e_b;

	e_a = a;
	e_b = b;
	if (e_a->st.st_mtim.tv_sec != e_b->st.st_mtim.tv_sec)
		return (e_b->st.st_mtim.tv_sec - e_a->st.st_mtim.tv_sec);
	else
		return (ft_strcmp(e_a->name, e_b->name));
}
