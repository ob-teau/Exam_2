/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alice <acoinus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:18:59 by alice             #+#    #+#             */
/*   Updated: 2022/02/14 11:50:16 by alice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_free(char *s)
{
	if (s)
		free(s);
	return (NULL);
}

int	check_n(char *s, char c, int x)
{
	int	i = -1;

	if (!s || (c != '\n' && c != '\0'))
		return (0);
	while (s[++i])
		if (s[i] == c)
			return (i);
	if (c == '\0' || x)
		return (i);
	return (0);
}

char	*ft_join(char *s1, char *s2)
{
	char *s;
	int	i = 0;
	int	j = 0;

	s = malloc(sizeof(char) * (check_n(s1, '\0', 0) + (check_n(s2, '\0', 0)) + 1));
	if (s == NULL)
		return (NULL);
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

char	*ft_line(t_info *f, char *rest)
{
	f->line = malloc(sizeof(char) * check_n(rest, '\n', 1) + 2);
	if (f->line == NULL)
		return (ft_free(rest));
	f->i = -1;
	while (rest && rest[++f->i] && rest[f->i] != '\n')
		f->line[f->i] = rest[f->i];
	if (rest && rest[f->i] == '\n' && f->i++ != -42)
		f->line[f->i - 1] = rest[f->i - 1];
	f->line[f->i] = '\0';
	f->tmp = rest;
	rest = ft_join(NULL, &f->tmp[f->i]);
	free(f->tmp);
	if (!rest)
		return (NULL);
	if (!rest[0])
		return (ft_free(rest));
	return (rest);
}

char *get_next_line(int fd)
{
	static char	*rest;
	t_info		f;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, f.save, 0) < 0)
		ft_free(rest);
	f.x_r = 1;
	while (!check_n(rest, '\n', 0) && f.x_r != 0)
	{
		f.x_r = read(fd, f.save, BUFFER_SIZE);
		if (f.x_r == -1)
			return (ft_free(rest));
		f.save[f.x_r] = '\0';
		f.tmp = rest;
		rest = ft_join(f.tmp, f.save);
		free(f.tmp);
		if (rest == NULL)
			return (NULL);
	}
	rest = ft_line(&f, rest);
	if (f.x_r == 0 && !rest && !f.line[0])
		return (ft_free(f.line));
	return (f.line);
}

int	main(int ac, char **av)
{
	int	fd;
	char *line;

	fd = open(av[1], O_RDONLY);
	printf("fd = [%d], ac = [%d]\n", fd, ac);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("line = [%s]\n", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

