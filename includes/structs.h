/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:14:32 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 19:07:42 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS
# define STRUCTS

typedef struct s_opt {
    int list;
    int all;
    int time;
    int reverse;
    int recursive;
}   t_opt;

typedef struct s_file {
    char *name;
    char *path;
    struct stat *stat;
}   t_file;

typedef struct s_dir {
    char *name;
    char *path;
    struct stat *stat;
    t_file **files;
    struct s_dir *next;
}   t_dir;

#endif