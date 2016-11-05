/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt_l.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/05 16:28:04 by qle-guen          #+#    #+#             */
/*   Updated: 2016/11/05 19:24:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "malloc.h"
#include "libft/libft.h"
#include "libprintf/libprintf.h"
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

static void		get_l_ent(t_ent *ent, t_fmt_l *l_ent, t_cat *cat)
{
	struct passwd	*user;
	struct group	*group;

	if (ent->ignore)
		return ;
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
		l_ent->lnk = readlink_s(ent, cat);
}

static void		time_field(time_t *ent_time)
{
	char		mon[3];
	char		day[3];
	char		last[5];
	char		*stime;
	time_t		now;

	stime = ctime(ent_time);
	ft_memcpy(mon, stime + 4, 3);
	day[0] = stime[8];
	day[1] = stime[9] == ' ' ? '\0' : stime[9];
	time(&now);
	if ((*ent_time + SIXMONTHS > now && *ent_time <= now))
		ft_memcpy(last, stime + 11, 5);
	else
	{
		ft_memcpy(last, stime + 20, 4);
		last[4] = ' ';
	}
	FMT(" %.3s %.2s %.5s", mon, day, last);
}

static void		fmt_l_ent_max(t_ent *ent, t_fmt_l *l_ent, size_t *l_ent_max)
{
	time_t		ent_t;

	if (ent->ignore)
		return ;
	ent_t = entry_gettime(ent);
	FMT("%c%c%c%c%c%c%c%c%c%c %*s %-*s %-*s", entry_type(ent->st.st_mode)
		, MODE(S_IRUSR, 'r'), MODE(S_IWUSR, 'w'), MODE(S_IXUSR, 'x')
		, MODE(S_IRGRP, 'r'), MODE(S_IWGRP, 'w'), MODE(S_IXGRP, 'x')
		, MODE(S_IROTH, 'r'), MODE(S_IWOTH, 'w'), MODE(S_IXOTH, 'x')
		, MAXLINKS, l_ent->links, MAXUSR, l_ent->usr, MAXGRP, l_ent->grp);
	if (NEEDMAJMIN(ent->st.st_mode))
		FMT(" %*s,%*s", MAXMA, l_ent->major, MAX(MAXSIZE, MAXMI), l_ent->minor);
	else
		FMT(" %*s", MAX(MAXSIZE, MAXMI) + MAXMA + 1, l_ent->size);
	time_field(&ent_t);
	FMT(" %s", ent->name);
	FMT(S_ISLNK(ent->st.st_mode) ? " -> %s\n" : "\n", l_ent->lnk);
}

static void		handle_max_values
	(t_ent *ent, t_fmt_l *l_ent, size_t *l_ent_max, size_t *total)
{
	*total += ent->st.st_size;
	IMAX_LEN(MAXLINKS, l_ent->links);
	IMAX_LEN(MAXUSR, l_ent->usr);
	IMAX_LEN(MAXGRP, l_ent->grp);
	IMAX_LEN(MAXSIZE, l_ent->size);
	if (NEEDMAJMIN(ent->st.st_mode))
	{
		IMAX_LEN(MAXMA, l_ent->major);
		IMAX_LEN(MAXMI, l_ent->minor);
	}
}

void			fmt_l(t_ent **ents, size_t n, t_cat *cat)
{
	size_t		i;
	size_t		l_ent_max[6];
	size_t		total;
	t_fmt_l		*l_ents;

	MALLOC(l_ents, sizeof(*l_ents) * n);
	ft_bzero(&l_ent_max, sizeof(l_ent_max));
	total = 0;
	i = -1;
	while (++i < n)
	{
		get_l_ent(ents[i], l_ents + i, cat);
		handle_max_values(ents[i], l_ents + i, l_ent_max, &total);
	}
	if (cat)
		FMT("total %lu\n", total / 512);
	i = -1;
	while (++i < n)
	{
		fmt_l_ent_max(ents[i], l_ents + i, l_ent_max);
		if (S_ISLNK(ents[i]->st.st_mode))
			free(l_ents[i].lnk);
		FLUSH;
	}
	free(l_ents);
}
