#include "libasm.h"

static t_line *ligh_low_quarter(char *l, int cnt, int i, int n_line)
{
	if (cnt == 301)
		return (ft_add_aff(l, cnt, i, n_line));
	else if (cnt == 307)
		return (ft_add_and(l, cnt, i, n_line));
	else if (cnt == 313)
		return (ft_add_ldi(l, cnt, i, n_line));
	else if (cnt == 316)
		return (ft_add_lld(l, cnt, i, n_line));
	ft_error_order(n_line, 2, NULL, NULL);
	return (NULL);
}

static t_line *high_half(char *l, int cnt, int i, int n_line)
{
	if (cnt <= 421)
	{
		if (cnt == 330)
			return (ft_add_sub(l, cnt, i, n_line));
		else if (cnt == 336)
			return (ft_add_sti(l, cnt, i, n_line));
		else if (cnt == 345)
			return (ft_add_xor(l, cnt, i, n_line));
		else if (cnt == 421)
			return (ft_add_lldi(l, cnt, i, n_line));
	}
	else if (cnt >= 432)
	{
		if (cnt == 432)
			return (ft_add_live(l, cnt, i, n_line));
		else if (cnt == 434)
			return (ft_add_fork(l, cnt, i, n_line));
		else if (cnt == 449)
			return (ft_add_zjmp(l, cnt, i, n_line));
		else if (cnt == 542)
			return (ft_add_lfork(l, cnt, i, n_line));
	}
	ft_error_order(n_line, 2, NULL, NULL);
	return (NULL);
}

t_line	*ft_add_new_line(char *l, int cnt, int i, int n_line)
{
	if (cnt <= 316 && cnt >= 208)
	{
		if (cnt <= 297)
		{
			if (cnt == 208)
				return (ft_add_ld(l, cnt, i, n_line));
			else if (cnt == 225)
				return (ft_add_or(l, cnt, i, n_line));
			else if (cnt == 231)
				return (ft_add_st(l, cnt, i, n_line));
			else if (cnt == 297)
				return (ft_add_add(l, cnt, i, n_line));
		}
		else
			return (ligh_low_quarter(l, cnt, i, n_line));
	}
	else if (cnt >=330 && cnt <= 542)
		return (high_half(l, cnt, i, n_line));
	ft_error_order(n_line, 2, NULL, NULL);
	return (NULL);
}
