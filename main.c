/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:32:06 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/04 05:44:51 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include "libvect/libvect.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>

static t_opts			get_opt(char *arg)
{
	t_opts		ret;

	ret = 0;
	while (*arg)
	{
		if (*arg == 'l')
			ret |= O_L;
		else if (*arg == 'R')
			ret |= O_UR;
		else if (*arg == 'a')
			ret |= O_A;
		else if (*arg == 'r')
			ret |= O_R;
		else if (*arg == 't')
			ret |= O_T;
		else
			ls_exit("illegal option -- %c\n%s", *arg, g_usage);
		arg++;
	}
	return (ret);
}

static t_f_lst			*build_fl(char **t, t_vect *m_buf, size_t *lsize)
{
	t_f_lst		*fl;
	t_stat		st;

	if (!*t)
		return (NULL);
	if (stat(*t, &st) == -1)
		ft_dprintf(2, g_stat_warn, *t, strerror(errno));
	if (!(st.st_mode & S_IFDIR))
	{
		vect_fmt(m_buf, "%s\n", *t);
		(*lsize)++;
		return (build_fl(t + 1, m_buf, lsize));
	}
	fl = malloc(sizeof(*fl));
	if (!fl)
		ls_exit(g_malloc_err, sizeof(*fl));
	fl->stat = st;
	fl->fn = *t;
	(*lsize)++;
	fl->next = build_fl(t + 1, m_buf, lsize);
	return (fl);
}

static int				ls_mask
	(t_f_lst *fl, t_opts opts, size_t lsize, t_vect *m_buf)
{
	if (!fl)
		return (1);
	if (lsize > 1 || OPT(O_R))
		vect_fmt(m_buf, "%s:\n", fl->fn);
	if (fl->stat.st_mode & S_IFDIR)
		ft_ls(fl->fn, opts, m_buf);
	if (m_buf->used >= BUFSIZ)
		m_buf_flush(m_buf);
	return (ls_mask(fl->next, opts, lsize, m_buf));
}

int						main(int argc, char **argv)
{
	int		i;
	t_opts	opts;
	t_f_lst	*fl;
	t_vect	m_buf;
	size_t	lsize;

	i = 1;
	opts = 0;
	lsize = 0;
	while (i < argc && argv[i][0] == '-')
		opts |= get_opt(&argv[i++][1]);
	ft_bzero(&m_buf, sizeof(m_buf));
	if (i == argc)
	{
		ft_ls(".", opts, &m_buf);
		return (m_buf_flush(&m_buf));
	}
	argv += i;
	sort_quicksort(argv, (size_t)(argc - i), &sort_lex);
	fl = build_fl(argv, &m_buf, &lsize);
	return (ls_mask(fl, opts, lsize, &m_buf)
		&& m_buf_flush(&m_buf));
}
