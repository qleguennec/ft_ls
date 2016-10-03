/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:32:06 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/03 20:47:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static unsigned long	get_opt(char *arg)
{
	unsigned long		ret;

	ret = 0;
	while (*arg)
	{
		if (*arg == 'l')
			ret |= L;
		else if (*arg == 'R')
			ret |= UR;
		else if (*arg == 'a')
			ret |= A;
		else if (*arg == 'r')
			ret |= R;
		else if (*arg == 't')
			ret |= T;
		else
			ls_exit("illegal option -- %c\n%s", *arg, g_usage);
		arg++;
	}
	return (ret);
}

static void				sort_args(char **t, int n)
{
	int		i;
	int		j;
	char	*p;
	char	*tmp;

	if (n < 2)
		return ;
	p = t[n / 2];
	i = 0;
	j = n - 1;
	while (42)
	{
		while (ft_strcmp(t[i], p) < 0)
			i++;
		while (ft_strcmp(p, t[j]) < 0)
			j--;
		if (i >= j)
			break ;
		tmp = t[i];
		t[i] = t[j];
		t[j--] = tmp;
		i++;
	}
	sort_args(t, i);
	sort_args(t + i, n - i);
}

static t_f_lst			*build_fl(char **t)
{
	t_f_lst		*fl;
	int			ret;

	if (!*t)
		return (NULL);
	fl = malloc(sizeof(*fl));
	if (!fl)
		ls_exit("malloc: failed to allocate %lu bytes", sizeof(*fl));
	ret = stat(*t, &fl->stat);
	if (ret == -1)
		ft_dprintf(2, "ls: cannot access '%s': %s\n", *t, strerror(errno));
	fl->fn = *t;
	fl->next = build_fl(t + 1);
	return (fl);
}

int						main(int argc, char **argv)
{
	int		i;
	t_opts	opts;
	t_f_lst	*fl;

	i = 1;
	opts = 0;
	while (i < argc && argv[i][0] == '-')
		opts |= get_opt(&argv[i++][1]);
	argv += i;
	sort_args(argv, argc - i);
	fl = build_fl(argv);
}
