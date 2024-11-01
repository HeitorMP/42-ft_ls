/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_dir_stats.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:26:29 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 19:45:19 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir   *ft_dirnew(char *name, char *path, struct stat *stat, t_file **files)
{
    t_dir   *dir;

    dir = NULL;
    if (!(dir = (t_dir *)malloc(sizeof(t_dir))))
        return (NULL);
    dir->name = name;
    dir->path = path;
    dir->stat = stat;
    dir->files = files;
    dir->next = NULL;
    return (dir);
}

t_dir   *ft_add_dir_back(t_dir **dir, t_dir *new)
{
    t_dir   *tmp;

    tmp = NULL;
    if (!dir)
        return (NULL);
    if (!*dir)
    {
        *dir = new;
        return (new);
    }
    tmp = *dir;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (new);
}

t_dir *setup_basic(const char **paths)
{
    t_dir *dir_list = NULL;
    t_dir *current_dir;
    DIR *dir;
    struct dirent *entry;
    int i, j;

    i = 0;
    while (paths[i])
    {
        // Cria um novo diretório e o adiciona à lista
        current_dir = ft_dirnew(ft_strdup(paths[i]), ft_strdup(paths[i]), NULL, NULL);
        if (!current_dir)
            return (NULL);
        ft_add_dir_back(&dir_list, current_dir);

        // Abre o diretório atual
        if (!(dir = opendir(paths[i])))
        {
            perror("opendir");
            return (NULL);
        }

        // Configura estatísticas do diretório
        current_dir->stat = (struct stat *)malloc(sizeof(struct stat));
        if (!current_dir->stat || lstat(paths[i], current_dir->stat) == -1)
        {
            perror("lstat");
            closedir(dir);
            return (NULL);
        }

        // Conta o número de arquivos no diretório para alocar a lista
        j = 0;
        while ((entry = readdir(dir)))
            j++;
        closedir(dir);  // Fecha o diretório para reabrir depois

        // Aloca a lista de arquivos do diretório
        current_dir->files = (t_file **)malloc(sizeof(t_file *) * (j + 1));
        if (!current_dir->files)
            return (NULL);
        current_dir->files[j] = NULL;

        // Reabre o diretório para ler os arquivos
        dir = opendir(paths[i]);
        if (!dir)
        {
            perror("opendir");
            return (NULL);
        }

        // Itera sobre os arquivos e configura estatísticas de cada um
        j = 0;
        while ((entry = readdir(dir)))
        {
            // Ignora "." e ".."
            if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                continue;

            // Cria uma nova estrutura de arquivo
            t_file *new_file = (t_file *)malloc(sizeof(t_file));
            if (!new_file)
                return (NULL);
            new_file->name = ft_strdup(entry->d_name);

            // Configura o caminho completo do arquivo
            char *tmp = ft_strjoin(paths[i], "/");
            new_file->path = ft_strjoin(tmp, entry->d_name);
            free(tmp);

            // Configura estatísticas do arquivo
            new_file->stat = (struct stat *)malloc(sizeof(struct stat));
            if (!new_file->stat || lstat(new_file->path, new_file->stat) == -1)
            {
                perror("lstat");
                return (NULL);
            }
            current_dir->files[j++] = new_file;
        }
        current_dir->files[j] = NULL;

        closedir(dir);
        i++;
    }
    return (dir_list);
}

t_dir *setup_recursive(const char *path)
{
    // Cria o nodo do diretório atual
    t_dir *current_dir = ft_dirnew(ft_strdup(path), ft_strdup(path), NULL, NULL);
    if (!current_dir)
        return NULL;

    DIR *dir = opendir(path);
    if (!dir)
    {
        perror("opendir");
        free(current_dir->name);
        free(current_dir->path);
        free(current_dir);
        return NULL;
    }

    // Aloca espaço para estatísticas do diretório atual
    current_dir->stat = (struct stat *)malloc(sizeof(struct stat));
    if (!current_dir->stat || lstat(path, current_dir->stat) == -1)
    {
        perror("lstat");
        closedir(dir);
        free(current_dir->stat);
        free(current_dir->name);
        free(current_dir->path);
        free(current_dir);
        return NULL;
    }

    struct dirent *entry;
    
    while ((entry = readdir(dir)))
    {
        if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
            continue;
        char *full_path = NULL;
        if (!(path[ft_strlen(path) - 1] == '/'))
            full_path = ft_strjoin(path, "/");
        else
            full_path = ft_strdup(path);
        char *new_path = ft_strjoin(full_path, entry->d_name);
        free(full_path);

        struct stat entry_stat;
        if (lstat(new_path, &entry_stat) == 0 && S_ISDIR(entry_stat.st_mode))
        {
            t_dir *subdir = setup_recursive(new_path);
            if (subdir)
                ft_add_dir_back(&current_dir, subdir);
        }
        free(new_path);
    }

    closedir(dir);

    return current_dir;
}


t_dir *setup_dir_stats(const char **paths, const t_opt opt)
{
    t_dir *dir_list = NULL;
    if (opt.recursive)
    {
        for (int i = 0; paths[i] != NULL; i++)
        {
            t_dir *new_dir = setup_recursive(paths[i]);
            if (new_dir)
                ft_add_dir_back(&dir_list, new_dir);
        }
    } else {
        dir_list = setup_basic(paths);
    }
    return dir_list;
}

