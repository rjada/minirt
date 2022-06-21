/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coverand <coverand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:22:13 by coverand          #+#    #+#             */
/*   Updated: 2022/06/21 15:22:29 by coverand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	ft_check_extension(char *file)
{
	char	*dot;

	dot = ft_strrchr(file, '.');
	if (!dot)
		ft_errors_handler(WRONG_EXTENSION);
	if (strcmp(dot, ".rt"))
		ft_errors_handler(WRONG_EXTENSION);
}

void	ft_init_scene(char *filename, t_scene __unused *scene)
{
	int		fd;
	char	*line;
	char	**elements;

	ft_memset(scene, 0, sizeof(t_scene));
	fd = open(filename, O_RDWR);
	if (fd < 0)
		ft_errors_handler(strerror(errno));
	line = get_next_line(fd);
	while (line)
	{
		if (line && strcmp(line, "\n"))
		{
			elements = ft_split(line, ' ');
			ft_get_elements(elements, scene);
		}
		free(line);
		free(elements);
		line = get_next_line(fd);
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	if (argc != 2)
		ft_errors_handler(ARGS_COUNT_FAILURE);
	ft_check_extension(argv[1]);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		ft_errors_handler(strerror(errno));
	ft_init_scene(argv[1], scene);
	return (0);
}
