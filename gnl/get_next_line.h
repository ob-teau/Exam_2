/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alice <acoinus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 16:23:28 by alice             #+#    #+#             */
/*   Updated: 2022/02/13 18:09:33 by alice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINEH

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_info
{
	int		x_r;
	int		i;
	char	save[BUFFER_SIZE + 1];
	char	*tmp;
	char	*line;
}	t_info;

#endif
