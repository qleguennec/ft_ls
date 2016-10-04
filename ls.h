/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:27:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/04 05:40:32 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libvect/libvect.h"
# include <stdlib.h>
# include <sys/stat.h>

# define VECT_EXIT_FUNCTION		ls_exit("malloc error");
# define OPT(x)					(opts & x)
# define O_L					1
# define O_UR					1 << 1
# define O_A					1 << 2
# define O_R					1 << 3
# define O_T					1 << 4
# define MAX_DIR_ENTS			10240

typedef unsigned long			t_opts;
typedef struct stat				t_stat;
typedef struct dirent			t_dirent;

typedef struct					s_f_lst
{
	char						*fn;
	t_stat						stat;
	struct s_f_lst				*next;
}								t_f_lst;

static const char				g_usage[] = "usage: ls [-lRart] [file ...]";
static const char				g_stat_warn[] = "ls: cannot access '%s': %s\n";
static const char				g_malloc_err[] = "malloc: failed to allocate %lu bytes";

int								m_buf_flush(t_vect *m_buf);
int								sort_lex(void *a, void *b);
void							ft_ls(char *fn, t_opts opts, t_vect *m_buf);
void							ls_exit(const char *format, ...);
void							sort_quicksort(void *t, int n, int (*cmp)(void *, void *));

#endif
