/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:32:06 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/03 15:46:14 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include <string.h>
#include <stdlib.h>

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
			ls_exit("ls: illegal option -- %c\n%s", *arg, usage);
		arg++;
	}
	return (ret);
}

static void				get_filename(t_f_lst ***fl, char *arg)
{
	**fl = ft_memalloc(sizeof(***fl));
	if (!**fl)
		ls_exit("malloc of size %lu failed", sizeof(***fl));
	while (*arg)
	{
		(**fl)->fn[(**fl)->fnlen++] = *arg++;
		if ((**fl)->fnlen == sizeof((**fl)->fn) - 1)
			ls_exit("arg too long");
	}
	*fl = &(**fl)->next;
}

static void				test_args(t_f_lst *fl, t_opts opts)
{
	if (OPT(L))
		ft_printf("l option\n");
	if (OPT(UR))
		ft_printf("R option\n");
	if (OPT(A))
		ft_printf("a option\n");
	if (OPT(R))
		ft_printf("r option\n");
	if (OPT(T))
		ft_printf("t option\n");
	while (fl)
	{
		ft_printf("%s\n", fl->fn);
		fl = fl->next;
	}
}

int						main(int argc, char **argv)
{
	int		i;
	t_opts	opts;
	t_f_lst	*flstart;
	t_f_lst	**fl;

	i = 1;
	opts = 0;
	flstart = NULL;
	fl = &flstart;
	while (i < argc)
	{
		if (!flstart && argv[i][0] == '-')
			opts |= get_opt(&argv[i][1]);
		else
			get_filename(&fl, argv[i]);
		i++;
	}
	test_args(flstart, opts);
}
