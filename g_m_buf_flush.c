/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_m_buf_flush.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 05:32:20 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/05 00:57:39 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libvect/libvect.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

void			g_m_buf_flush(void)
{
	if (!g_m_buf.used)
		return ;
	if (write(1, g_m_buf.data, g_m_buf.used) == -1)
		ls_exit("ls: cannot write %lu bytes of data on stdout: %s"
			, g_m_buf.data
			, strerror(errno));
	g_m_buf.used = 0;
}
