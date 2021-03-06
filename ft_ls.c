/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 19:12:28 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/06 16:47:32 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "malloc.h"
#include "libprintf/libprintf.h"
#include "libvect/libvect.h"
#include "libft/libft.h"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

static size_t	get_n_ents(char *dn)
{
	DIR			*dir;
	size_t		n;
	t_dirent	*ent;

	dir = opendir(dn);
	if (!dir)
	{
		WARN(g_open_warn, dn);
		g_ret = 1;
		return (0);
	}
	n = 0;
	while ((ent = readdir(dir)))
		n += ent->d_name[0] != '.' || INC_POINT_ENT;
	closedir(dir);
	return (n);
}

static void		get_dir_contents
	(char *dn, t_ent **ents, size_t *maxlen)
{
	DIR			*dir;
	t_dirent	*dir_ent;

	if (!(dir = opendir(dn)))
	{
		g_ret = 1;
		WARN(g_open_warn, dn);
		return ;
	}
	while ((dir_ent = readdir(dir)))
	{
		if (dir_ent->d_name[0] == '.' && !INC_POINT_ENT)
			continue ;
		MALLOC_SIZEOF(*ents);
		(*ents)->name = ft_strdup(dir_ent->d_name);
		IMAX(*maxlen, ft_strlen(dir_ent->d_name));
		ents++;
	}
	closedir(dir);
}

static void		retrieve_data
	(char *dn, t_ent **ents, size_t n, t_cat *cat)
{
	size_t		i;

	if (NEEDCAT)
		fn_concat(dn, cat);
	if (NEEDSTAT)
	{
		i = -1;
		while (++i < n)
		{
			ft_strcpy(cat->p, ents[i]->name);
			if ((ents[i]->ignore = lstat(cat->name, &ents[i]->st) == -1)
				&& (g_ret = 1))
				WARN(g_access_warn, cat->name);
		}
	}
}

static void		re_ls(t_ent **ents, size_t n, t_cat *cat)
{
	size_t		i;

	i = -1;
	while (++i < n)
	{
		if ((!(INC_POINT_ENT && (!STRCMP(ents[i]->name, ".")
			|| !STRCMP(ents[i]->name, ".."))))
			&& (ENT_ISDIR(ents[i]->st))
			&& !ents[i]->ignore)
		{
			ft_strcpy(cat->p, ents[i]->name);
			FMT("\n%s:\n", cat->name);
			ft_ls(cat->name);
			FLUSH;
		}
	}
}

void			ft_ls(char *dn)
{
	size_t		n;
	t_cat		cat;
	t_ent		**ents;

	if (!(n = get_n_ents(dn)))
		return ;
	MALLOC(ents, sizeof(*ents) * n);
	cat.maxlen = 0;
	get_dir_contents(dn, ents, &cat.maxlen);
	retrieve_data(dn, ents, n, &cat);
	ls_sort_ents(ents, n);
	if (g_flags['l'])
		fmt_l(ents, n, &cat);
	else
		fmt(ents, n, cat.maxlen);
	if (g_flags['R'])
		re_ls(ents, n, &cat);
	if (NEEDCAT)
		free(cat.name);
	free_ents(ents, n);
}
