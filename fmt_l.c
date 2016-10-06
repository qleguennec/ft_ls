/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:28:04 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/06 20:55:12 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

static char		entry_type(mode_t m)
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

static void		get_l_ent(t_ent *ent, t_fmt_l *l_ent, size_t *l_ent_max)
{
	struct passwd	*user;
	struct group	*group;

	user = getpwuid(ent->st.st_uid);
	group = getgrgid(ent->st.st_gid);
	ft_strcpy(l_ent->usr, user->pw_name);
	ft_strcpy(l_ent->grp, group->gr_name);
	ft_sprintf(l_ent->links, "%d", ent->st.st_nlink);
	ft_sprintf(l_ent->size, "%d", ent->st.st_size);
	IMAX_LEN(l_ent_max[0], l_ent->links);
	IMAX_LEN(l_ent_max[1], l_ent->usr);
	IMAX_LEN(l_ent_max[2], l_ent->grp);
	IMAX_LEN(l_ent_max[3], l_ent->size);
}

static void		fmt_l_ent_max(t_ent *ent, t_fmt_l *l_ent, size_t *l_ent_max)
{
	vect_fmt(&g_m_buf, "%c%c%c%c%c%c%c%c%c%c %*s %*s %*s %*s %s\n"
		, entry_type(ent->st.st_mode)
		, MODE(ent->st.st_mode, S_IRUSR, 'r')
		, MODE(ent->st.st_mode, S_IWUSR, 'w')
		, MODE(ent->st.st_mode, S_IXUSR, 'x')
		, MODE(ent->st.st_mode, S_IRGRP, 'r')
		, MODE(ent->st.st_mode, S_IWGRP, 'w')
		, MODE(ent->st.st_mode, S_IXGRP, 'x')
		, MODE(ent->st.st_mode, S_IROTH, 'r')
		, MODE(ent->st.st_mode, S_IWOTH, 'w')
		, MODE(ent->st.st_mode, S_IXOTH, 'x')
		, l_ent_max[0]
		, l_ent->links
		, l_ent_max[1]
		, l_ent->usr
		, l_ent_max[2]
		, l_ent->grp
		, l_ent_max[3]
		, l_ent->size
		, ent->name);
}

void			fmt_l(t_ent **ents, size_t n)
{
	size_t		i;
	size_t		l_ent_max[4];
	t_fmt_l		l_ents[n];

	i = -1;
	ft_bzero(&l_ent_max, sizeof(l_ent_max));
	while (++i < n)
		get_l_ent(ents[i], l_ents + i, l_ent_max);
	i = -1;
	while (++i < n)
		fmt_l_ent_max(ents[i], l_ents + i, l_ent_max);
}
