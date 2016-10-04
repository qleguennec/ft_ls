/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 19:12:28 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/05 00:28:18 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libprintf/libprintf.h"
#include "libvect/libvect.h"
#include "libft/libft.h"
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

static size_t	get_n_ents(char *fn)
{
	DIR			*dir;
	size_t		n_ents;
	t_dirent	*ent;

	dir = opendir(fn);
	if (!dir)
	{
		WARN(g_open_warn, fn);
		return (0);
	}
	n_ents = 0;
	while ((ent = readdir(dir)))
		n_ents += ent->d_name[0] != '.' || g_flags['a'];
	closedir(dir);
	return (n_ents);
}

static void		get_dir_contents
	(char *fn, char **dir_ents, size_t n_ents)
{
	DIR			*dir;
	char		*s;
	size_t		d_len;
	size_t		i;
	t_dirent	*ent;

	i = 0;
	if (!(dir = opendir(fn)))
		return (WARN(g_open_warn, fn));
	while (i < n_ents)
	{
		ent = readdir(dir);
		if (ent->d_name[0] == '.' && !g_flags['a'])
			continue ;
		d_len = ft_strlen(ent->d_name);
		MALLOC_HANDLE(s, d_len + 1);
		ft_memcpy(s, ent->d_name, d_len);
		s[d_len] = '\0';
		dir_ents[i++] = s;
	}
	closedir(dir);
}

static int		fmt(char **dir_ents, size_t n_ents)
{
	size_t		i;

	i = 0;
	while (i < n_ents)
		vect_fmt(&g_m_buf, "%s\n", dir_ents[i++]);
	return (1);
}

static void		re_ls(char *dir_ent, char *bn)
{
	t_vect		v;
	t_stat		st;

	if (dir_ent[0] == '.')
		return ;
	ft_bzero(&v, sizeof(v));
	vect_addstr(&v, bn);
	if (bn[v.used - 1] != '/')
		vect_addstr(&v, "/");
	vect_addstr(&v, dir_ent);
	vect_mset_end(&v, '\0', 1);
	if (lstat(v.data, &st) == -1)
		WARN(g_access_warn, v.data);
	else if (st.st_mode & S_IFDIR && !(st.st_mode & S_IFLNK))
	{
		vect_fmt(&g_m_buf, "\n%s:\n", v.data);
		ft_ls(v.data);
	}
	if (g_m_buf.used >= BUFSIZ)
		g_m_buf_flush();
	free(dir_ent);
	free(v.data);
}

void			ft_ls(char *fn)
{
	char		**dir_ents;
	size_t		i;
	size_t		n_ents;

	if (!(n_ents = get_n_ents(fn)))
		return ;
	MALLOC_HANDLE(dir_ents, sizeof(char *) * n_ents);
	get_dir_contents(fn, dir_ents, n_ents);
	sort_quicksort(dir_ents, n_ents, &sort_lex);
	i = 0;
	if (fmt(dir_ents, n_ents) && g_flags['R'])
	{
		i = 0;
		while (i < n_ents)
			re_ls(dir_ents[i++], fn);
		free(dir_ents);
	}
}
