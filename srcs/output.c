/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:12:43 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 19:37:25 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void print_file_stat(const char *file_path, const char *file_name) {
    struct stat file_stat;

    if (lstat(file_path, &file_stat) == -1) {
        perror("lstat");
        return;
    }

    // Exibir permissões e tipo de arquivo
    ft_printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    ft_printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    ft_printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    ft_printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    // Outros atributos: links, UID, GID, tamanho
    ft_printf(" %d", file_stat.st_nlink);
    ft_printf(" %d", file_stat.st_uid);
    ft_printf(" %d", file_stat.st_gid);
    ft_printf(" %d", file_stat.st_size);

    // Extrair data e formatar como "MMM DD"
    char *date_str = ctime(&file_stat.st_mtime);
    char month_day[8]; // Buffer para "Mmm dd\0"
    if (date_str) {
        for (int i = 0; i < 7; i++) {
            month_day[i] = date_str[i + 4]; // Copia de 4 a 10
        }
        month_day[7] = '\0'; // Finaliza a string
        ft_printf(" %s", month_day);
    } else {
        ft_printf(" ErroData");
    }

    // Nome do arquivo
    ft_printf(" %s\n", file_name);
}



void list_output(const t_dir *dir_list) {
    const t_dir *current_dir = dir_list;

    while (current_dir) {
        ft_printf("Directory: %s\n", current_dir->path);
        
        // Abrir o diretório e listar arquivos
        DIR *dir = opendir(current_dir->path);
        if (!dir) {
            perror("opendir");
            return;
        }

        struct dirent *entry;
        while ((entry = readdir(dir))) {
            // Ignorar "." e ".."
            if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
                continue;

            // Criar o caminho completo para o arquivo
            char *file_path = ft_strjoin(current_dir->path, "/");
            char *full_path = ft_strjoin(file_path, entry->d_name);
            free(file_path);

            // Imprimir as estatísticas do arquivo usando `print_file_stat`
            print_file_stat(full_path, entry->d_name);

            free(full_path);
        }

        closedir(dir);

        ft_printf("\n");
        current_dir = current_dir->next; // Avança para o próximo diretório
    }
}


void    print_dir_names(const t_dir *dir_list)
{
    const t_dir *current_dir = dir_list;

    while (current_dir)
    {
        ft_printf("%s\n", current_dir->name);
        current_dir = current_dir->next;
    }
}