/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpoh <jpoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:57:51 by jpoh              #+#    #+#             */
/*   Updated: 2026/10/08 16:58:06 by jpoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    :+:      :+:    :+:   */
/*   By: student <student@42.fr>                      +:+ +:+         +:+     */
/*  +#+#+#+#+#+   +#+   +#+   +#+            #+#    #+# visually #          */
/*  Created: 2026/10/08 16:48:00 by student           #+#    #+#             */
/*  Updated: 2026/10/08 16:48:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_newline(char *stash)
{
	int	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*init_empty_stash(void)
{
	char	*stash;

	stash = malloc(1);
	if (!stash)
		return (NULL);
	stash[0] = '\0';
	return (stash);
}

char	*ft_strjoin(char *stash, const char *buffer)
{
	char	*str;
	int		slen;
	int		blen;
	int		i;

	if (!stash)
		stash = init_empty_stash();
	if (!stash || !buffer)
		return (free(stash), NULL);
	slen = 0;
	while (stash && stash[slen])
		slen++;
	blen = 0;
	while (buffer && buffer[blen])
		blen++;
	str = malloc(slen + blen + 1);
	if (!str)
		return (free(stash), NULL);
	i = -1;
	while (++i < slen)
		str[i] = stash[i];
	while (*buffer)
		str[i++] = *buffer++;
	return (str[i] = '\0', free(stash), str);
}
