/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:32:06 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/07 20:25:30 by qle-guen         ###   ########.fr       */
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

	i = 0;
	while (*arg)
	{
		while (i <= LEN(g_impl_flags) && *arg != g_impl_flags[i])
			i++;
		if (i == LEN(g_impl_flags))
			ls_exit("illegal option -- %c\n%s", *arg, g_usage);
		g_flags[(int)*arg] = 1;
		arg++;
	}
}

static void				ls_count(char **argv, size_t *ndirs, size_t *nfiles)
{
	t_stat	st;

	*ndirs = 0;
	*nfiles = 0;
	while (*argv)
	{
		if (stat(*argv, &st) == -1)
			WARN(g_access_warn, *argv);
		else
		{
			*ndirs += S_ISDIR(st.st_mode);
			*nfiles += !S_ISDIR(st.st_mode);
		}
		argv++;
	}
}

static void				ls_print
	(char **dirs, size_t ndirs, t_ent **files, size_t nfiles)
{
	size_t	i;

	if (g_flags['l'])
		fmt_l(files, nfiles, NULL);
	else
		fmt(files, nfiles);
	i = -1;
	while (++i < ndirs)
	{
		if ((nfiles + ndirs > 1 || g_flags['R']) && !i && !nfiles)
			vect_fmt(&g_m_buf, "%s:\n", dirs[i]);
		else if (nfiles + ndirs > 1 || g_flags['R'])
			vect_fmt(&g_m_buf, "\n%s:\n", dirs[i]);
		ft_ls(dirs[i]);
		FLUSH;
	}
	if (ndirs)
		free(dirs);
	if (nfiles)
		free(files);
}

static void				ls_start(char **argv)
{
	char	**dirs;
	size_t	ndirs;
	size_t	nfiles;
	t_ent	**files;
	t_stat	st;

	ls_count(argv--, &ndirs, &nfiles);
	if (!(ndirs || nfiles))
		return ;
	MALLOC(dirs, sizeof(*dirs) * ndirs);
	MALLOC(files, sizeof(*files) * nfiles);
	while (*++argv)
	{
		if (stat(*argv, &st) == -1)
			continue ;
		if (S_ISDIR(st.st_mode))
			*dirs++ = *argv;
		else
		{
			MALLOC_SIZEOF(*files);
			(*files)->name = *argv;
			ft_memcpy(&(*files++)->st, &st, sizeof(st));
		}
	}
	ls_print(dirs - ndirs, ndirs, files - nfiles, nfiles);
}

int						main(int argc, char **argv)
{
	int		i;

	i = 1;
	ft_bzero(&g_m_buf, sizeof(g_m_buf));
	ft_bzero(&g_flags, LEN(g_flags));
	while (i < argc && argv[i][0] == '-')
		get_flags(&argv[i++][1]);
	if (i == argc)
	{
		if (g_flags['R'])
			vect_fmt(&g_m_buf, ".:\n");
		ft_ls(".");
		buf_flush();
		return (0);
	}
	argv += i;
	argc -= i;
	i = 0;
	sort_quicksort((void **)argv, (size_t)argc, &sort_lex);
	ls_start(argv);
	buf_flush();
	return (0);
}
