/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:32:06 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/05 18:32:51 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "malloc.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include "libvect/libvect.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

static void				get_flags(char *arg)
{
	size_t		i;

	while (*arg)
	{
		i = 0;
		while (i < LEN(g_impl_flags) && *arg != g_impl_flags[i])
			i++;
		if (i == LEN(g_impl_flags) && *arg != g_impl_flags[i - 1])
			ls_exit(2, "illegal option -- %c\n%s", *arg, g_usage);
		g_flags[(int)*arg] = 1;
		arg++;
	}
}

static void				ls_count(char **argv)
{
	t_stat	st;

	g_ndirs = 0;
	g_nfiles = 0;
	while (*argv)
	{
		if (stat(*argv, &st) == -1 && (g_ret = 2))
			WARN(g_access_warn, *argv);
		else
		{
			g_ndirs += ENT_ISDIR(st);
			g_nfiles += !ENT_ISDIR(st);
		}
		argv++;
	}
}

static void				ls_print(t_ent **dirs, t_ent **files, size_t maxlen)
{
	size_t	i;

	g_ncols = term_getsize();
	if (g_flags['l'])
		fmt_l(files, g_nfiles, NULL);
	else
		fmt(files, g_nfiles, maxlen);
	i = -1;
	while (++i < g_ndirs)
	{
		if ((g_nfiles + g_ndirs > 1 || g_flags['R']) && !i && !g_nfiles)
			vect_fmt(&g_m_buf, "%s:\n", dirs[i]->name);
		else if (g_nfiles + g_ndirs > 1 || g_flags['R'])
			vect_fmt(&g_m_buf, "\n%s:\n", dirs[i]->name);
		ft_ls(dirs[i]->name);
		FLUSH;
	}
	if (g_ndirs)
		free(dirs);
	if (g_nfiles)
		free(files);
}

static void				ls_start(char **argv)
{
	size_t	maxlen;
	t_ent	**dirs;
	t_ent	**files;
	t_ent	*ent;

	if (!(g_ndirs || g_nfiles))
		return ;
	MALLOC(dirs, sizeof *dirs * g_ndirs);
	MALLOC(files, sizeof(*files) * g_nfiles);
	maxlen = 0;
	while (*argv)
	{
		if ((ent = entry(*argv++, NULL)) && ENT_ISDIR(ent->st))
			*dirs++ = ent;
		else
		{
			IMAX(maxlen, ft_strlen(ent->name));
			*files++ = ent;
		}
	}
	ls_sort_ents(dirs - g_ndirs, g_ndirs);
	ls_sort_ents(files - g_ndirs, g_ndirs);
	ls_print(dirs - g_ndirs, files - g_nfiles, maxlen);
}

int						main(int argc, char **argv)
{
	int		i;
	char	*noarg;

	i = 1;
	ft_bzero(&g_m_buf, sizeof(g_m_buf));
	ft_bzero(&g_flags, LEN(g_flags));
	noarg = NULL;
	g_ret = 0;
	while (i < argc && argv[i][0] == '-')
		get_flags(&argv[i++][1]);
	if (i == argc)
		noarg = ft_strdup(".");
	argv += i;
	argc -= i;
	i = 0;
	ls_sort(argv, (size_t)argc);
	ls_count(noarg ? &noarg : argv);
	ls_start(noarg ? &noarg : argv);
	buf_flush();
	free(noarg);
	return (g_ret);
}
