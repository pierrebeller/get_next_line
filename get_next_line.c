/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 10:49:17 by pbeller           #+#    #+#             */
/*   Updated: 2017/01/18 10:49:34 by pbeller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

int	stock_gestion(int fd, char **stock, char **line)
{
	char	*temp;
	int		len;

	temp = *line;
	if (!ft_strchr(stock[fd], '\n'))
	{
		*line = ft_strjoin(*line, stock[fd]);
		return (fill_buff(fd, stock, line));
	}
	else
	{
		len = ft_strchr(stock[fd], '\n') - stock[fd];
		temp = ft_strjoin(temp, ft_strsub(stock[fd], 0, len));
		stock[fd] = ft_strsub(stock[fd], len + 1,\
		ft_strlen(stock[fd]) - len - 1);
		*line = temp;
		return (1);
	}
}

int	fill_buff(int fd, char **stock, char **line)
{
	int		ret;
	int		len;
	char	buff[BUFF_SIZE + 1];
	char	*temp;

	temp = *line;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (ret < 0)
			return (-1);
		buff[ret] = 0;
		if (ft_strchr(buff, '\n') == NULL)
			temp = ft_strjoin(temp, buff);
		else if (ft_strchr(buff, '\n'))
		{
			len = ft_strchr(buff, '\n') - buff;
			temp = ft_strjoin(temp, ft_strsub(buff, 0, len));
			stock[fd] = ft_strsub(buff, len + 1, ft_strlen(buff) - len - 1);
			*line = temp;
			return (1);
		}
	}
	return (ret > 0 ? ret : ft_strlen(stock[fd]));
}

int	get_next_line(int fd, char **line)
{
	static	char	*stock[255];
	int				ret;

	*line = ft_strnew(BUFF_SIZE + 1);
	if (fd < 0 || !line)
		return (-1);
	else if (!stock[fd])
	{
		ret = fill_buff(fd, stock, line);
		return (ret > 0 ? ret : ft_strlen(stock[fd]));
	}
	else
	{
		ret = stock_gestion(fd, stock, line);
		return (ret > 0 ? ret : ft_strlen(stock[fd]));
	}
	return (ret > 0 ? ret : ft_strlen(stock[fd]));
}
