/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrhiba <yrhiba@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 02:43:18 by yrhiba            #+#    #+#             */
/*   Updated: 2022/10/16 16:35:49 by yrhiba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_line_3(char *content, char *nw_content, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (content[i] != '\n')
	{
		line[i] = content[i];
		i++;
	}
	line[i++] = '\n';
	line[i] = '\0';
	j = 0;
	while (content[i])
		nw_content[j++] = content[i++];
	nw_content[j] = '\0';
}

char	*get_line_2(char **content, int index)
{
	char	*line;
	char	*nw_content;

	line = (char *)malloc(sizeof(char) * (index + 2));
	if (!line)
		return (NULL);
	nw_content = (char *)malloc(sizeof(char) * (ft_strlen(*content) - index));
	if (!nw_content)
	{
		free(line);
		return (NULL);
	}
	get_line_3(*content, nw_content, line);
	free(*content);
	*content = nw_content;
	return (line);
}

char	*get_line_1(char **content, int fd)
{
	char	*line;
	int		r;

	r = 1;
	while (ft_strchr(*content) == -1 && r != 0)
		*content = read_content(*content, fd, &r);
	if (!*content)
		return (NULL);
	if (ft_strchr(*content) == -1)
		return (NULL);
	line = get_line_2(content, ft_strchr(*content));
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*line;

	content = 0;
	if (!content)
	{
		content = (char *)malloc(sizeof(char));
		if (!content)
			return (NULL);
		*content = '\0';
	}
	line = get_line_1(&content, fd);
	return (line);
}
