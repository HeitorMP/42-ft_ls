/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:36:14 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 19:16:01 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;

    t_opt   opt;
    init_opt_struct(&opt);

    if (!setup_opt(&opt, argv))
        return (2);

    ft_printf("flags:\n-l: %d\n-a: %d\n-r: %d\n-R: %d\n-t: %d\n", opt.list, opt.all, opt.reverse, opt.recursive, opt.time);
    ft_printf("--------------------------------\n\n");

    char **paths;
    paths = setup_paths(argv);

    t_dir *dir_stats;

    dir_stats = setup_dir_stats((const char**)paths, (const t_opt)opt);

    if (opt.list)
        list_output((const t_dir *)dir_stats);
    else
        print_dir_names((const t_dir *)dir_stats);
    
    // clean_all(&dir_stats, paths);
    return 0;
}
