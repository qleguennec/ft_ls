/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:05:04 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/05 18:35:27 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"

void			ls_sort(char **t, size_t n)
{
	if (g_flags['f'])
		return ;
	ft_qsort((void **)t, n, &sort_lex, g_flags['r']);
}

void			ls_sort_ents(t_ent **t, size_t n)
{
	if (g_flags['f'])
		return ;
	if (g_flags['t'])
		ft_qsort((void **)t, n, &sort_mtim, g_flags['r']);
	else if (g_flags['r'])
		ft_qsort((void **)t, n, &sort_lex, 1);
}
