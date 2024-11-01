/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 15:27:45 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 16:05:51 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    ft_clean_dir_lst(t_dir **dir)
{
    t_dir   *tmp = NULL;
    t_dir   *next = NULL;
    int     i;

    i = 0;
    tmp = *dir;
    while (tmp)
    {
        next = tmp->next;
        free(tmp->name);
        free(tmp->path);
        free(tmp->stat);
        while (tmp->files[i])
        {
            free(tmp->files[i]->name);
            free(tmp->files[i]->path);
            free(tmp->files[i]->stat);
            free(tmp->files[i]);
            i++;
        }
        i = 0;
        free(tmp->files);
        free(tmp);
        tmp = next;
    }
    *dir = NULL;
}

void    clean_all(t_dir **dir, char **paths)
{
    ft_clean_dir_lst(dir);
    ft_free_array_by_null(paths);
}