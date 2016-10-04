/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 19:12:28 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/04 05:37:03 by qle-guen         ###   ########.fr       */
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

static size_t	get_dir_contents
	(DIR *dir, char **dir_ents, t_opts opts)
{
	char		*s;
	size_t		d_len;
	size_t		i;
	t_dirent	*ent;

	i = 0;
	while (i < MAX_DIR_ENTS)
	{
		ent = readdir(dir);
		if (!ent)
			break ;
		if (ent->d_name[0] == '.' && !OPT(O_A))
			continue ;
		d_len = ft_strlen(ent->d_name);
		s = malloc(d_len + 1);
		if (!s)
			ls_exit(g_malloc_err, ft_strlen(ent->d_name));
		ft_memcpy(s, ent->d_name, d_len);
		s[d_len] = '\0';
		dir_ents[i++] = s;
	}
	return (i);
}

static int		fmt
	(char **dir_ents, size_t n_ents, t_vect *m_buf)
{
	size_t		i;

	i = 0;
	while (i < n_ents)
		vect_fmt(m_buf, "%s\n", dir_ents[i++]);
	return (1);
}

static void		re_ls
	(char *dir_ent, char *bn, t_opts opts, t_vect *m_buf)
{
	t_vect		v;
	t_stat		st;

	ft_bzero(&v, sizeof(v));
	vect_addstr(&v, bn);
	if (bn[v.used - 1] != '/')
		vect_addstr(&v, "/");
	vect_addstr(&v, dir_ent);
	vect_mset_end(&v, '\0', 1);
	if (stat(v.data, &st) == -1)
		ft_dprintf(2, g_stat_warn, v.data, strerror(errno));
	else if (st.st_mode & S_IFDIR)
	{
		vect_fmt(m_buf, "\n%s:\n", v.data);
		ft_ls(v.data, opts, m_buf);
	}
	if (m_buf->used >= BUFSIZ)
		m_buf_flush(m_buf);
	free(dir_ent);
	free(v.data);
}

void			ft_ls(char *fn, t_opts opts, t_vect *m_buf)
{
	DIR			*dir;
	char		*dir_ents[MAX_DIR_ENTS];
	size_t		i;
	size_t		n_ents;

	dir = opendir(fn);
	if (!dir)
		return ((void)ft_dprintf(2, "ls: cannot open '%s': %s\n"
			, fn, strerror(errno)));
	n_ents = get_dir_contents(dir, dir_ents, opts);
	if (n_ents == MAX_DIR_ENTS)
		ls_exit("too many entries in directory: '%s'", fn);
	sort_quicksort(dir_ents, n_ents, &sort_lex);
	if (fmt(dir_ents, n_ents, m_buf) && OPT(O_UR))
	{
		i = 0;
		while (i < n_ents)
			re_ls(dir_ents[i++], fn, opts, m_buf);
	}
}
