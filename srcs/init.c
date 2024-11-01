/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:17:24 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 13:47:05 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    init_opt_struct(t_opt *opt)
{
    opt->list = 0;
    opt->all = 0;
    opt->reverse = 0;
    opt->recursive = 0;
    opt->time = 0;
}

void    init_dir_stats(t_dir **dir_stats)
{
    int i;

    i = 0;
    while (dir_stats[i])
    {
        dir_stats[i]->name = NULL;
        dir_stats[i]->path = NULL;
        dir_stats[i]->stat = NULL;
        dir_stats[i]->files = NULL;
        i++;
    }
}
