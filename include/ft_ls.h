/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/15 03:45:41 by qle-guen          #+#    #+#             */
/*   Updated: 2016/01/15 03:55:05 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef struct		s_ls_ops
{
	unsigned int	long_format		: 1;
	unsigned int	recursive		: 1;
	unsigned int	include_dot		: 1;
	unsigned int	reverse_order	: 1;
	unsigned int	sortby_time		: 1;
}					t_ls_ops;

#endif
