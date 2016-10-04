/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_buf_flush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/04 05:32:20 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/04 05:36:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libvect/libvect.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int				m_buf_flush(t_vect *m_buf)
{
	if (!m_buf->used)
		return (1);
	if (write(1, m_buf->data, m_buf->used) == -1)
		ls_exit("ls: cannot write %lu bytes of data on stdout: %s"
			, m_buf->data
			, strerror(errno));
	m_buf->used = 0;
	return (0);
}
