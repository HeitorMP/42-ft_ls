/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaciel- <hmaciel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:12:42 by hmaciel-          #+#    #+#             */
/*   Updated: 2024/11/01 12:40:05 by hmaciel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_free_array_by_null(char **array)
{
    int i;

    i = 0;

    if (!array)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    if (array)
        free(array);
}

void    ft_free_array_by_size(char **array, size_t size)
{
    size_t i;

    i = 0;

    if (!array)
        return ;
    while (i < size)
    {
        free(array[i]);
        i++;
    }
    if (array)
        free(array);
}