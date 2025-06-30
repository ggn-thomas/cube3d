/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:56:22 by thgaugai          #+#    #+#             */
/*   Updated: 2025/06/30 16:41:48 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_print(char **map)
{
	int	i = 0;

	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	counter_line(char *file)
{
	int	fd;
	char *line;
	int	counter;
	
	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: File descriptor is invalid!");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		counter++;
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return (counter);
}

char	**map_init(char *file)
{
	char **map;
	char *line;
	int	i;
	int	fd;
	int count;

	count = counter_line(file);
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error: Cannot open file!\n");
		exit(EXIT_FAILURE);
	}
	map = malloc(sizeof(char*) * (count + 1));
	if (!map)
	{
		printf("Error: Memomy allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		map[i] = ft_strdup(line);
		if (!map[i])
		{
			printf("Error: Memomy allocation failed!\n");
			ft_free_map(map);
		}
		free(line);
		line = NULL;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	main(int ac, char **av)
{
	(void)ac;
	char	**map;
	
	map = map_init(av[1]);
	game_engine(map);
	return (0);
}
