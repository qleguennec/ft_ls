/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:54:13 by qle-guen          #+#    #+#             */
/*   Updated: 2016/10/07 21:00:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>

# define MALLOC_F			malloc
# define MALLOC_ERR(x)		ft_malloc_err(x, __FUNCTION__, __FILE__, __LINE__)

# define MALLOC(p, x)		if (!(p = MALLOC_F(x))) MALLOC_ERR(x)
# define MALLOC_SIZEOF(p)	MALLOC(p, sizeof(*p))

void						*ft_null(size_t size);
void						ft_malloc_err
	(size_t size, const char *func, const char *file, int line);

#endif
