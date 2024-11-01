/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:24:00 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 14:33:43 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int count_paths(const char *argv[])
{
    int i;
    int count;

    i = 1;
    count = 0;
    while (argv[i])
    {
        if (argv[i][0] != '-' || (argv[i][0] == '-'  && ft_strlen(argv[i]) == 1))
            count++;
        i++;
    }
    return (count);
}

char **setup_paths(const char *argv[])
{
    char **paths;
    int i;
    int count;

    i = 1;
    count = count_paths(argv);
    
    paths = (char **)malloc(sizeof(char *) * (count + 1));
    if (!paths)
        return (NULL);
    i = 1;
    count = 0;
    while (argv[i])
    {
        if (argv[i][0] != '-' || (argv[i][0] == '-'  && ft_strlen(argv[i]) == 1))
        {
            paths[count] = ft_strdup(argv[i]);
            count++;
        }
        i++;
    }
    paths[count] = NULL;
    return (paths);
}