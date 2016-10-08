/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:47:04 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/08 00:29:42 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "malloc.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include "libvect/libvect.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void		fn_concat(char *bn, t_cat *cat)
{
	size_t	blen;
	size_t	total;

	blen = ft_strlen(bn);
	total = blen + cat->maxlen + 1 + (bn[blen - 1] != '/');
	MALLOC(cat->name, total);
	ft_strncpy(cat->name, bn, total);
	if (bn[blen - 1] != '/')
		cat->name[blen++] = '/';
	cat->p = cat->name + blen;
}

void		buf_flush(void)
{
	if (!g_m_buf.used)
		return ;
	if (write(1, g_m_buf.data, g_m_buf.used) == -1)
		ls_exit("ls: cannot write %lu bytes of data on stdout: %s"
			, g_m_buf.data
			, strerror(errno));
	g_m_buf.used = 0;
}

char		*readlink_s(t_ent *ent, t_cat *cat)
{
	char	*fn;
	char	*ret;
	ssize_t	n;

	if (cat)
		ft_strcpy(cat->p, ent->name);
	fn = cat->name;
	MALLOC(ret, ent->st.st_size + 1);
	n = readlink(fn, ret, ent->st.st_size + 1);
	if (n == -1)
		WARN(g_read_warn, fn);
	ret[ent->st.st_size] = '\0';
	return (ret);
}

char		entry_type(mode_t m)
{
	if (S_ISSOCK(m))
		return ('s');
	if (S_ISLNK(m))
		return ('l');
	if (S_ISREG(m))
		return ('-');
	if (S_ISBLK(m))
		return ('b');
	if (S_ISDIR(m))
		return ('d');
	if (S_ISCHR(m))
		return ('c');
	if (S_ISFIFO(m))
		return ('p');
	return ('?');
}

void		free_ents(t_ent **ents, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		free(ents[i]->name);
		free(ents[i]);
		i++;
	}
	free(ents);
}
