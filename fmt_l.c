/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:28:04 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/06 23:17:12 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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
	if (user)
		ft_strcpy(l_ent->usr, user->pw_name);
	else
		ft_sprintf(l_ent->usr, "%d", ent->st.st_uid);
	if (group)
		ft_strcpy(l_ent->grp, group->gr_name);
	else
		ft_sprintf(l_ent->grp, "%d", ent->st.st_gid);
	ft_sprintf(l_ent->links, "%d", ent->st.st_nlink);
	ft_sprintf(l_ent->size, "%d", ent->st.st_size);
	IMAX_LEN(l_ent_max[0], l_ent->links);
	IMAX_LEN(l_ent_max[1], l_ent->usr);
	IMAX_LEN(l_ent_max[2], l_ent->grp);
	IMAX_LEN(l_ent_max[3], l_ent->size);
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
	mon[0] = ft_tolower(mon[0]);
	day[0] = time[8];
	day[1] = time[9] == ' ' ? '\0' : time[9];
	last_time_field(last, time, &ent->st.st_mtim.tv_sec);
	vect_fmt(&g_m_buf
		, "%c%c%c%c%c%c%c%c%c%c %*s %-*s %-*s %*s %.3s. %.2s %.5s %s\n"
		, entry_type(ent->st.st_mode)
		, MODE(S_IRUSR, 'r'), MODE(S_IWUSR, 'w'), MODE(S_IXUSR, 'x')
		, MODE(S_IRGRP, 'r'), MODE(S_IWGRP, 'w'), MODE(S_IXGRP, 'x')
		, MODE(S_IROTH, 'r'), MODE(S_IWOTH, 'w'), MODE(S_IXOTH, 'x')
		, l_ent_max[0], l_ent->links
		, l_ent_max[1], l_ent->usr
		, l_ent_max[2], l_ent->grp
		, l_ent_max[3], l_ent->size
		, mon, day, last
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
	{
		fmt_l_ent_max(ents[i], l_ents + i, l_ent_max);
		FLUSH;
	}
}
