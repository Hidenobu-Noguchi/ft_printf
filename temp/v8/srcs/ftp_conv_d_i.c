/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_conv_d_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:53:38 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/07/05 21:07:24 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	puts_not_width(char *str, t_fmt_info *ifo, size_t in, size_t ptn)
{
	size_t	sign;
	size_t	puts_prec_len;

	sign = 0;
	puts_prec_len = 0;
	if (ftp_put_flags_plus_space(ifo) == -1)
		return (-1);
	if (in < ptn)
	{
		puts_prec_len = ptn - in;
		if (str[0] == '-')
		{
			if (write(1, &str[0], 1) == -1)
				return (-1);
			sign += 1;
		}
		if (ftp_puts_character('0', puts_prec_len) == -1)
			return (-1);
		if (write(1, &str[sign], (ptn - sign - puts_prec_len)) == -1)
			return (-1);
	}
	else
		if (write(1, str, in) == -1)
			return (-1);
	return (1);
}

static size_t	adjust_info_puts_len(t_fmt_info *info, int i, size_t *i_len)
{
	size_t	sign_flag;
	size_t	puts_len;

	puts_len = 0;
	sign_flag = 0;
	if (i < 0)
		sign_flag = 1;
	if ((info->precision != -1)
		&& (*i_len - sign_flag) < (size_t)info->precision)
		puts_len = (size_t)info->precision + sign_flag;
	else if (i == 0 && info->precision == 0)
	{
		puts_len = 0;
		*i_len = 0;
	}
	else
		puts_len = *i_len;
	if (sign_flag == 1)
		info->bit_flag &= ~(1 << 2);
	if (puts_len < (size_t)info->width || sign_flag == 1)
		info->bit_flag &= ~(1 << 3);
	return (puts_len);
}

int	ftp_conv_d_i(int i, t_fmt_info *info, char *buf, size_t *p_len)
{
	size_t	buf_len;
	size_t	i_len;
	size_t	puts_len;
	char	*i_str;

	buf_len = ft_strlen(buf);
	i_str = ftp_itoa_count(i, &i_len);
	if (i_str == NULL)
		return (-1);
	puts_len = adjust_info_puts_len(info, i, &i_len);
	if (ftp_check_len_cnt(p_len, buf_len, puts_len, info) == -1)
		return (ftp_free_null(&i_str));
	if (write(1, buf, buf_len) == -1)
		return (ftp_free_null(&i_str));
	if (puts_len < (size_t)info->width)
	{
		if (ftp_puts_d_i(i_str, info, i_len, puts_len) == -1)
			return (ftp_free_null(&i_str));
	}
	else
		if (puts_not_width(i_str, info, i_len, puts_len) == -1)
			return (ftp_free_null(&i_str));
	(void)ftp_free_null(&i_str);
	return (1);
}
