/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_conv_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 11:19:59 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/06/29 18:46:24 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ftp_conv_c(char c, t_fmt_info *info, char *buf, size_t *p_len)
{
	size_t	buf_len;

	buf_len = ft_strlen(buf);
	if (ftp_check_len_count(p_len, buf_len, 1, (size_t)info->width) == -1)
		return (-1);
	if (1 < info->width)
	{
		if (write(1, buf, buf_len) == -1)
			return (-1);
		if (ftp_puts_format_c_s(&c, info, 1) == -1)
			return (-1);
	}
	else
		if (ftp_puts_conv_only(buf, &c, buf_len, 1) == -1)
			return (-1);
	return (1);
}
