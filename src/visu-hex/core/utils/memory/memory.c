/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edos-san <edos-san@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 22:15:49 by edos-san          #+#    #+#             */
/*   Updated: 2022/06/25 14:24:18 by edos-san         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Engine.h"

void *free_list(void **values)
{
	int i;

	if (values)
	{
		i = -1;
		while (values[++i])
			free(values[i]);
		free(values);
		return (NULL);
	}
	return (NULL);
}

void *ft_calloc(size_t __size)
{
	void *v;
	unsigned char *temp;

	if (__size < 1)
		return (NULL);
	v = malloc(__size);
	if (!v)
		engine()->destroy("Error");
	temp = (unsigned char *)v;
	while (__size-- > 0)
		*(temp++) = (unsigned char)0;
	return (v);
}

void *ft_realloc(void *ptr, size_t newsize)
{
	char *newptr;
	unsigned char *tmp;
	int i;
	size_t cursize;

	if (ptr == 0)
		return (ft_calloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	tmp = (unsigned char *)ptr;
	i = -1;
	while (tmp[i++])
		newptr[i] = tmp[i];
	free(ptr);
	return (newptr);
}

void **this()
{
	static void *v;

	return (&v);
}
