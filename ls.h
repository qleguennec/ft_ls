/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:27:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/05 18:33:36 by qle-guen         ###   ########.fr       */
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
# define STR_SIZE(t)			3 * sizeof(t) + 1
# define WARN(w, x)				(void)ft_dprintf(2, w, __FUNCTION__, x, strerror(errno))
# define CMP(cmp, a, b)			((g_flags['r']) ? cmp(b, a) : cmp(a, b))
# define MODE(c, l)				((ent->st.st_mode & c) ? l : '-')
# define IMAX(a, b)				(a = a >= b ? a : b)
# define IMAX_LEN(a, s)			IMAX(a, ft_strlen(s))
# define ITOENT(s, f)			ft_sprintf(s->f, "%d", s->st->f)
# define BUF_SIZ				20 * 1024
# define FLUSH					if (g_m_buf.used >= BUF_SIZ) buf_flush()
# define STRCMP					ft_strcmp

# define MAXLINKS				l_ent_max[0]
# define MAXUSR					l_ent_max[1]
# define MAXGRP					l_ent_max[2]
# define MAXSIZE				l_ent_max[3]
# define MAXMAJOR				l_ent_max[4]
# define MAXMINOR				l_ent_max[5]

//# define NEEDSTAT				(g_flags['R'] || g_flags['t'] || g_flags['l'])
# define NEEDSTAT				1
# define NEEDCAT				NEEDSTAT
# define NEEDMAJMIN(dev)		(S_ISBLK(dev) || S_ISCHR(dev))
# define INC_POINT_ENT			(g_flags['a'])

# define ENT_ISDIR(x)			(!g_flags['d'] && S_ISDIR(x.st_mode))

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
	unsigned int				ignore : 1;
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
static const char				*g_access_warn = "ls: '%s()' cannot access '%s': %s\n";
static const char				*g_impl_flags = "Rlartdf";
static const char				*g_open_warn = "ls: '%s()' cannot open '%s': %s\n";
static const char				*g_read_warn = "ls: '%s()' cannot read '%s': %s\n";
static const char				*g_usage = "usage: ls [-lRart] [file ...]";
size_t							g_nfiles;
size_t							g_ndirs;
char							g_flags[127];
t_vect							g_m_buf;
int								g_ret;
int								g_ncols;

char							*readlink_s(t_ent *ent, t_cat *cat);
char							entry_type(mode_t m);
int								sort_ent_lex(void *a, void *b);
int								sort_lex(void *a, void *b);
int								sort_mtim(void *a, void *b);
int								term_getsize(void);
t_ent							*entry(char *fn, t_cat *cat);
t_ent							*get_entry(char *fn, t_cat *cat);
void							buf_flush(void);
void							fmt(t_ent **ents, size_t n, size_t maxlen);
void							fmt_l(t_ent **ents, size_t n, t_cat *cat);
void							fn_concat(char *bn, t_cat *cat);
void							free_ents(t_ent **ents, size_t n);
void							ft_ls(char *fn);
void							ls_exit(int ret, const char *format, ...);
void							ls_sort(char **t, size_t n);
void							ls_sort_ents(t_ent **t, size_t n);

#endif
