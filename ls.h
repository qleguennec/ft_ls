/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:27:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/05 00:22:09 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libvect/libvect.h"
# include <stdlib.h>
# include <sys/stat.h>

# define VECT_EXIT_FUNCTION		ls_exit("malloc error")
# define MALLOC_ERR(x)			ls_exit(g_malloc_err, x)
# define MALLOC_HANDLE(p, x)	if (!(p = malloc(x))) MALLOC_ERR(x)
# define WARN(w, x)				(void)ft_dprintf(2, w, x, strerror(errno))

typedef unsigned long			t_opts;
typedef struct stat				t_stat;
typedef struct dirent			t_dirent;

static const char				*g_usage = "usage: ls [-lRart] [file ...]";
static const char				*g_access_warn = "ls: cannot access '%s': %s\n";
static const char				*g_open_warn = "ls: cannot open '%s': %s\n";
static const char				*g_malloc_err = "malloc: failed to allocate %lu bytes";
static const char				*g_impl_flags = "Rlart";
char							g_flags[127];
t_vect							g_m_buf;

int								sort_lex(void *a, void *b);
void							ft_ls(char *fn);
void							ls_exit(const char *format, ...);
void							g_m_buf_flush(void);
void							sort_quicksort(void *t, int n, int (*cmp)(void *, void *));

#endif
