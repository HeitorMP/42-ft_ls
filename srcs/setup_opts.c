/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:57:27 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 12:41:33 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int set_opt_flag(t_opt *opt, char flag)
{
    switch (flag)
    {
    case 'l':
        opt->list = 1;
        break;
    case 'a':
        opt->all = 1;
        break;
    case 'r':
        opt->reverse = 1;
        break;
    case 't':
        opt->time = 1;
        break;
    case 'R':
        opt->recursive = 1;
        break;
    default:
        ft_putstr_fd("ft_ls: invalid option -- ", 2);
        ft_putchar_fd(flag, 2);
        ft_putstr_fd("\nusage: ft_ls [-Ralrt] [file ...]\n", 2);
        return (0);
        break;
    }
    return (1);
}

int setup_opt(t_opt *opt, const char *argv[])
{
    int i;

    i = 1;
    while(argv[i])
    {
        if (argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
        {
            int j = 1;
            while(argv[i][j])
            {
                if (!set_opt_flag(opt, argv[i][j]))
                    return (0);
                j++;
            }
        }
        i++;
    }
    return (1);
}