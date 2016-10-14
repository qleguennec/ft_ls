/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_getsize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 04:37:14 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/08 04:58:10 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int			term_getsize(void)
{
	int				fd;
	struct winsize 	s;

	fd = open("/dev/tty", O_RDONLY);
	ioctl(fd, TIOCGWINSZ, &s);
	close(fd);
	return (s.ws_col);
}
