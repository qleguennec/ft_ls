/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:28:04 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/07 01:36:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/kdev_t.h>

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

static void		get_l_ent(t_ent *ent, t_fmt_l *l_ent)
{
	struct passwd	*user;
	struct group	*group;

	group = getgrgid(ent->st.st_gid);
	if ((user = getpwuid(ent->st.st_uid)))
		ft_strcpy(l_ent->usr, user->pw_name);
	else
		ft_sprintf(l_ent->usr, "%u", ent->st.st_uid);
	if ((group = getgrgid(ent->st.st_gid)))
		ft_strcpy(l_ent->grp, group->gr_name);
	else
		ft_sprintf(l_ent->grp, "%u", ent->st.st_gid);
	ft_sprintf(l_ent->links, "%u", ent->st.st_nlink);
	if (NEEDMAJMIN(ent->st.st_mode))
	{
		ft_sprintf(l_ent->major, "%u", major(ent->st.st_dev));
		ft_sprintf(l_ent->minor, "%u", minor(ent->st.st_dev));
		*l_ent->size = '\0';
	}
	else
		ft_sprintf(l_ent->size, "%u", ent->st.st_size);
	if (S_ISLNK(ent->st.st_mode))
		readlink_s(ent->name, l_ent->lnk, sizeof(l_ent->lnk));
}

static void		last_time_field(char *s, char *t, time_t *ftime)
{
	time_t	now;

	time(&now);
	if ((*ftime + SIXMONTHS > now && *ftime <= now))
	{
		ft_memcpy(s, t + 11, 5);
		return ;
	}
	ft_memcpy(s, t + 20, 4);
	s[4] = ' ';
}

static void		fmt_l_ent_max(t_ent *ent, t_fmt_l *l_ent, size_t *l_ent_max)
{
	char		*time;
	char		mon[3];
	char		day[3];
	char		last[5];

	time = ctime(&ent->st.st_mtim.tv_sec);
	ft_memcpy(mon, time + 4, 3);
	day[0] = time[8];
	day[1] = time[9] == ' ' ? '\0' : time[9];
	last_time_field(last, time, &ent->st.st_mtim.tv_sec);
	vect_fmt(&g_m_buf, "%c%c%c%c%c%c%c%c%c%c %*s %-*s %-*s"
		, entry_type(ent->st.st_mode)
		, MODE(S_IRUSR, 'r'), MODE(S_IWUSR, 'w'), MODE(S_IXUSR, 'x')
		, MODE(S_IRGRP, 'r'), MODE(S_IWGRP, 'w'), MODE(S_IXGRP, 'x')
		, MODE(S_IROTH, 'r'), MODE(S_IWOTH, 'w'), MODE(S_IXOTH, 'x')
		, MAXLINKS, l_ent->links, MAXUSR, l_ent->usr, MAXGRP, l_ent->grp);
	if (NEEDMAJMIN(ent->st.st_mode))
		vect_fmt(&g_m_buf, " %*s,%*s"
			, MAXMAJOR, l_ent->major, MAX(MAXSIZE, MAXMINOR), l_ent->minor);
	else
		vect_fmt(&g_m_buf, " %*s"
			, MAX(MAXSIZE, MAXMINOR) + MAXMAJOR + 1, l_ent->size);
	vect_fmt(&g_m_buf, " %.3s %.2s %.5s %s", mon, day, last, ent->name);
	vect_fmt(&g_m_buf, S_ISLNK(ent->st.st_mode)
		? " -> %s\n" : "\n", l_ent->lnk);
}

void			fmt_l(t_ent **ents, size_t n)
{
	size_t		i;
	size_t		l_ent_max[6];
	t_fmt_l		l_ents[n];

	i = -1;
	ft_bzero(&l_ent_max, sizeof(l_ent_max));
	while (++i < n)
	{
		get_l_ent(ents[i], l_ents + i);
		IMAX_LEN(MAXLINKS, l_ents[i].links);
		IMAX_LEN(MAXUSR, l_ents[i].usr);
		IMAX_LEN(MAXGRP, l_ents[i].grp);
		IMAX_LEN(MAXSIZE, l_ents[i].size);
		if (NEEDMAJMIN(ents[i]->st.st_mode))
		{
			IMAX_LEN(MAXMAJOR, l_ents[i].major);
			IMAX_LEN(MAXMINOR, l_ents[i].minor);
		}
	}
	i = -1;
	while (++i < n)
	{
		fmt_l_ent_max(ents[i], l_ents + i, l_ent_max);
		FLUSH;
	}
}
