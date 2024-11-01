/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 09:34:33 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 19:09:02 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS
# define FT_LS

# include "../libft/includes/libft.h"
# include "structs.h"

# include <dirent.h> // opendir, readdir, closedir
# include <stdio.h> // perror
#include <time.h>  // ctime

void    init_opt_struct(t_opt *opt);
void    init_dir_stats(t_dir **dir_stats);
int     setup_opt(t_opt *opt, const char *argv[]);
char    **setup_paths(const char *argv[]);
void    print_dir_stats(const t_dir *dir_list);
t_dir   *setup_dir_stats(const char **paths, const t_opt opt);
void    clean_all(t_dir **dir, char **paths);
void    list_output(const t_dir *dir_list);
void    print_dir_names(const t_dir *dir_list);

#endif