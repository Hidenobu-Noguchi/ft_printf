/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_puts_d_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoguchi <hnoguchi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 20:34:35 by hnoguchi          #+#    #+#             */
/*   Updated: 2022/07/05 19:19:50 by hnoguchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int	puts_precision_str(char *str, size_t in, ssize_t sgn, size_t ptn)
{
	size_t	puts_prec_len;

	puts_prec_len = ptn - in;
	if (ftp_puts_character('0', puts_prec_len) == -1)
		return (-1);
	if (write(1, str, (ptn - sgn - puts_prec_len)) == -1)
		return (-1);
	return (1);
}

static int	puts_nflag_minus(char *str, t_fmt_info *ifo, size_t in, size_t ptn)
{
	size_t	sign;

	sign = 0;
	if (ftp_put_flags_plus_space(ifo) == -1)
		return (-1);
	else if (str[0] == '-')
		if (write(1, &str[sign++], 1) == -1)
			return (-1);
	if ((0 < ifo->width) && (ifo->bit_flag & (1 << 4)))
		if (ftp_puts_character('0', (size_t)ifo->width - in) == -1)
			return (-1);
	if (in < ptn)
	{
		if (puts_precision_str(&str[sign], in, sign, ptn) == -1)
			return (-1);
	}
	else
		if (write(1, &str[sign], (in - sign)) == -1)
			return (-1);
	return (1);
}

static int	puts_flag_minus(char *str, t_fmt_info *ifo, size_t in, size_t ptn)
{
	size_t	sign;

	sign = 0;
	if (ftp_put_flags_plus_space(ifo) == -1)
		return (-1);
	if (in < ptn)
	{
		if (str[0] == '-')
			if (write(1, &str[sign++], 1) == -1)
				return (-1);
		if (puts_precision_str(&str[sign], in, sign, ptn) == -1)
			return (-1);
	}
	else
		if (write(1, str, in) == -1)
			return (-1);
	return (1);
}

int	ftp_puts_d_i(char *str, t_fmt_info *ifo, size_t in, size_t ptn)
{
	size_t	flag_len;

	flag_len = 0;
	if ((ifo->bit_flag & (1 << 2)) || (ifo->bit_flag & (1 << 3)))
		flag_len = 1;
	if (ifo->bit_flag & (1 << 1))
	{
		if (puts_flag_minus(str, ifo, in, ptn) == -1)
			return (-1);
		if ((0 < ifo->width) && !(ifo->bit_flag & (1 << 4)))
			if (ftp_puts_character(' ',
					(size_t)ifo->width - flag_len - ptn) == -1)
				return (-1);
	}
	else
	{
		if ((0 < ifo->width) && !(ifo->bit_flag & (1 << 4)))
			if (ftp_puts_character(' ',
					(size_t)ifo->width - flag_len - ptn) == -1)
				return (-1);
		if (puts_nflag_minus(str, ifo, in, ptn) == -1)
			return (-1);
	}
	return (1);
}
