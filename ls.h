/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 14:27:00 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/03 15:46:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <stdlib.h>

# define OPT(a)			opts & a
# define L				1
# define UR				1 << 1
# define A				1 << 2
# define R				1 << 3
# define T				1 << 4

typedef unsigned long	t_opts;

typedef struct			s_f_lst
{
	char				fn[1024];
	size_t				fnlen;
	struct s_f_lst		*next;
}						t_f_lst;

static const char		usage[] = "usage: ls [-lRart] [file ...]";

void					ls_exit(const char *format, ...);

#endif
