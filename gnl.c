/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiyapan <npiyapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:26:40 by npiyapan          #+#    #+#             */
/*   Updated: 2024/03/22 16:35:58 by npiyapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int ft_strlen(char *src)
{
	int i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

void ft_strcpy(char *res, char *src, int len)
{
	int i;

	if (!src)
		return ;
	i = 0;
	while (i < len)
	{
		res[i] = src[i];
		i++;
	}
	res[i] = 0;
}

char *ft_strdup(char *src)
{
	char *res;
	int len;

	len = ft_strlen(src);
	res = malloc(sizeof(char) * len + 1);
	if (!res)
		return (NULL);
	ft_strcpy(res, src, len);
	return (res);
}

char *ft_strchr(char *src, char c)
{
	int i;

	i = 0;
	while (src[i])
	{
		if (src[i] == c)
			return (src + i);
		i++;
	}
	return (NULL);
}

char *ft_strjoin(char *src1, char *src2, size_t len2)
{
	char *res;
	int len1;
	
	if (!src1 || !src2)
		return (NULL);
	len1 = ft_strlen(src1);
	res = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, src1, len1);
	ft_strcpy(res + len1, src2, len2);
	res[len1 + len2] = 0;
	free (src1);
	return (res);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char *line;
	char *newline;
	int count;

	if (fd < 0)
		return (NULL);
	
	line = ft_strdup(buf);
	buf[0] = 0;
	while (!ft_strchr(line, '\n') && (count = read(fd, buf, BUFFER_SIZE)) > 0 )
	{
		// printf("read = %s\n", buf);
		buf[count] = 0;
		line = ft_strjoin(line, buf, count);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return(NULL);
	}
	newline = ft_strchr(line, '\n');
	if (newline)
	{
		// printf("newlline - line = %ld\n", newline - line);
		ft_strcpy(buf, newline + 1, BUFFER_SIZE + 1);
		// printf("buf = %s\n", buf);
		line[newline - line + 1] = 0;
	}
	return (line);
}

int main(void)
{
	int fd;
	char *line;
	char *a = "123abc";
	char *b;
	char *c = "zzz";
	char *res;

	// b = ft_strdup(a);
	// printf("b = %s\n", b);
	// res = ft_strjoin(b, c, 3);
	// printf("%s\n", res);
	// free(res);
	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s", line);
		// line = get_next_line(fd);
		// printf("line = %s", line);
		// line = get_next_line(fd);
		// printf("line = %s", line);
		if (!line)
			break;
	}

}