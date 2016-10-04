/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_quicksort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 23:16:41 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/05 01:44:54 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <stdlib.h>

void				sort_quicksort
	(void **t, size_t n, int (*cmp)(void *, void *))
{
	int		i;
	int		j;
	void	*p;
	void	*tmp;

	if (n < 2)
		return ;
	p = t[n / 2];
	i = 0;
	j = n - 1;
	while (42)
	{
		while (CMP(cmp, p, t[i]) > 0)
			i++;
		while (CMP(cmp, t[j], p) > 0)
			j--;
		if (i >= j)
			break ;
		tmp = t[i];
		t[i] = t[j];
		t[j--] = tmp;
		i++;
	}
	sort_quicksort(t, i, cmp);
	sort_quicksort(t + i, n - i, cmp);
}
