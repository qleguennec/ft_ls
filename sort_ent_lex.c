/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ent_lex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 23:23:01 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/08 03:26:20 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <string.h>

int			sort_ent_lex(void *a, void *b)
{
	t_ent	*e_a;
	t_ent	*e_b;

	e_a = (t_ent *)a;
	e_b = (t_ent *)b;
	return (strcoll((const char *)e_a->name, (const char *)e_b->name));
}
