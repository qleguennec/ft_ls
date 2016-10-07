/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:27:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/07 04:56:29 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libvect/libvect.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>

# define USR_GRP_MAX_LEN		32
# define SIXMONTHS				((365 / 2) * 86400)
# define VECT_EXIT_FUNCTION		ls_exit("malloc error")
# define MALLOC_ERR(x)			ls_exit(g_malloc_err, x)
# define MALLOC(p, x)			if (!(p = malloc(x))) MALLOC_ERR(x)
# define MALLOC_SIZEOF(p)		MALLOC(p, sizeof(*p))
# define STR_SIZE(t)			3 * sizeof(t) + 1
# define WARN(w, x)				(void)ft_dprintf(2, w, x, strerror(errno))
# define CMP(cmp, a, b)			((g_flags['r']) ? cmp(b, a) : cmp(a, b))
# define MODE(c, l)				((ent->st.st_mode & c) ? l : '-')
# define IMAX(a, b)				(a = a >= b ? a : b)
# define IMAX_LEN(a, s)			IMAX(a, ft_strlen(s))
# define ITOENT(s, f)			ft_sprintf(s->f, "%d", s->st->f)
# define BUF_SIZ				20 * 1024
# define FLUSH					if (g_m_buf.used >= BUF_SIZ) buf_flush()

# define MAXLINKS				l_ent_max[0]
# define MAXUSR					l_ent_max[1]
# define MAXGRP					l_ent_max[2]
# define MAXSIZE				l_ent_max[3]
# define MAXMAJOR				l_ent_max[4]
# define MAXMINOR				l_ent_max[5]

# define NEEDSTAT				(g_flags['R'] || g_flags['t'] || g_flags['l'])
# define NEEDCAT				NEEDSTAT
# define NEEDMAJMIN(dev)		S_ISBLK(dev) || S_ISCHR(dev)
# define INC_POINT_ENT			(g_flags['a'])

typedef unsigned long			t_opts;
typedef struct stat				t_stat;
typedef struct dirent			t_dirent;
typedef struct					s_cat
{
	char						*name;
	char						*p;
	size_t						maxlen;
}								t_cat;
typedef struct					s_ent
{
	char						*name;
	t_stat						st;
}								t_ent;
typedef struct					s_fmt_l
{
	char						links[STR_SIZE(unsigned int)];
	char						usr[USR_GRP_MAX_LEN + 1];
	char						grp[USR_GRP_MAX_LEN + 1];
	char						size[STR_SIZE(unsigned int)];
	char						major[STR_SIZE(unsigned int)];
	char						minor[STR_SIZE(unsigned int)];
	char						*lnk;
}								t_fmt_l;

static const char				*g_access_warn = "ls: cannot access '%s': %s\n";
static const char				*g_impl_flags = "Rlart";
static const char				*g_malloc_err = "malloc: failed to allocate %lu bytes";
static const char				*g_open_warn = "ls: cannot open '%s': %s\n";
static const char				*g_read_warn = "ls: cannot read '%s': %s\n";
static const char				*g_usage = "usage: ls [-lRart] [file ...]";
char							g_flags[127];
t_vect							g_m_buf;

char							*readlink_s(t_ent *ent, t_cat *cat);
char							entry_type(mode_t m);
int								sort_ent_lex(void *a, void *b);
int								sort_lex(void *a, void *b);
void							buf_flush(void);
void							fmt(t_ent **ents, size_t n);
void							fmt_l(t_ent **ents, size_t n, t_cat *cat);
void							fn_concat(char *bn, t_cat *cat);
void							free_ents(t_ent **ents, size_t n);
void							ft_ls(char *fn);
void							ls_exit(const char *format, ...);
void							sort_quicksort(void **t, size_t n, int (*cmp)(void *, void *));

#endif
