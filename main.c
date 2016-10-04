/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:32:06 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/05 01:27:58 by qle-guen         ###   ########.fr       */
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

static void				get_flags(char *arg)
{
	size_t		i;

	i = 0;
	while (*arg)
	{
		while (i < LEN(g_impl_flags) && *arg != g_impl_flags[i])
			i++;
		if (i == LEN(g_impl_flags))
			ls_exit("illegal option -- %c\n%s", *arg, g_usage);
		g_flags[(int)*arg] = 1;
		arg++;
	}
}

static void				ls_mask
	(char **argv, size_t argsize)
{
	int			ret;
	size_t		i;
	t_stat		st;

	i = 0;
	while (i < argsize)
	{
		if ((ret = stat(argv[i], &st)) == -1)
			WARN(g_access_warn, argv[i]);
		if (st.st_mode & S_IFDIR)
		{
			if (g_flags['R'])
				vect_fmt(&g_m_buf, "%s:\n", argv[i]);
			else if (argsize > 1)
				vect_fmt(&g_m_buf, "%s:\n", argv[i]);
			ft_ls(argv[i]);
		}
		else
			vect_fmt(&g_m_buf, "%s\n", argv[i]);
		if (g_m_buf.used >= BUFSIZ)
			g_m_buf_flush();
		i++;
	}
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
		ft_ls(".");
		g_m_buf_flush();
		return (0);
	}
	argv += i;
	argc -= i;
	i = 0;
	sort_quicksort((void **)argv, (size_t)argc, &sort_lex);
	ls_mask(argv, (size_t)argc);
	g_m_buf_flush();
	return (0);
}
