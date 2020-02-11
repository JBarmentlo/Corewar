/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarment <jbarment@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 15:29:48 by dberger           #+#    #+#             */
/*   Updated: 2020/02/11 10:03:36 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char    *ft_stricat(char *dest, const char *src, int indx_src)
{
    int i;
    int j;
    i = indx_src;
    j = 0;
    while (src[j])
    {
        dest[i + j] = src[j];
        j++;
    }
    dest[i + j] = '\0';
    return (dest);
}

int		init_file(t_file *out_file, char *source_file, int i)
{
	out_file->total_size = 0;
	out_file->prog_size = 0;
	out_file->name = ft_memalloc(i + 4);
	out_file->content = ft_memalloc(MAX_SIZE_FILE);
	out_file->name = ft_memcpy(out_file->name, source_file, i + 1); 
	out_file->name = ft_stricat(out_file->name, "cor", i + 1); 
	out_file->fd = open(out_file->name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if (out_file->fd <= 0)
		return (ft_error("Can't create the file", out_file->name));
	return (TRUE);
}

int		fill_header(t_file *out_file, int fd)
{
	(void)fd;
	// write magic number//
	nb_to_binary(out_file, sizeof(COREWAR_EXEC_MAGIC), out_file->total_size, COREWAR_EXEC_MAGIC);
	return (TRUE);
}

int		cor_file(char *source_file, t_file *out_file, int fd)
{	
	int		i;

	(void) fd;
	i = 0;
	while (source_file[i] && source_file[i] != '.')
		i++;
	if (source_file[i] == '\0' || source_file[i + 1] == '\0' || source_file[i + 1] != 's' || source_file[i + 2] != '\0')
		return (ft_error("Wrong source file format", NULL));
	if (init_file(out_file, source_file, i) == FALSE)
		return (FALSE);
	if (fill_header(out_file, fd) == FALSE)
		return (FALSE);
	//////////////////////////NICO MODIFICATIONS///////////////////////////
/*	t_stack		a;
	t_label		*save;

	save = a.label_list;
	a.champion_name = "zork";
	a.comment = "Bonjour le monde";
	a.label_list->name = "l2";
	a.label_list->opt = (char**)malloc(sizeof(char*) * 2);
	a.label_list->opt[0] = (char*)malloc(sizeof(char) * 19);
	a.label_list->opt[0] = "sti r1, %:live, %1\0";
	a.label_list->opt[1] = (char*)malloc(sizeof(char) * 15);
	a.label_list->opt[1] = "and r1, %0, r1\0";
	a.label_list = a.label_list->next;
	a.label_list->name = "live";
	a.label_list->opt = (char**)malloc(sizeof(char*) * 2);
	a.label_list->opt[0] = (char*)malloc(sizeof(char) * 8);
	a.label_list->opt[0] = "live %1\0";
	a.label_list->opt[1] = (char*)malloc(sizeof(char) * 12);
	a.label_list->opt[1] = "zjmp %:live\0";
	a.label_list = save;
*/
	/*
	** CHAMPION_NAME SUR 128 OCTETS
	*/
/*
	i = 0;
	while (i < 128)
	{
		if (i < (int)ft_strlen(a.champion_name))
			out_file->content[out_file->total_size] = a.champion_name[i];
		else
			out_file->content[out_file->total_size] = 0;
		out_file->total_size += 1;
		i++;
	}
*/
	/*
	** 4 OCTETS A NULL
	*/
/*
	i = 0;
	while (i < 4)
	{
		out_file->content[out_file->total_size] = 0;
		out_file->total_size += 1;
		i++;
	}
*/
	/*
	** TAILLE DE L'EXE EN OCTETS ?
	** je met a 0 pour l'instant vu que je sais pas
	*/
/*
	i = 0;
	while (i < 4)
	{
		out_file->content[out_file->total_size] = 0;
		out_file->total_size += 1;
		i++;
	}
*/
	/*
	** COMMENT SUR 2048 OCTETS
	** COMMENT_LENGHT ?
	*/
/*
	i = 0;
	while (i < 2048)
	{
		if (i < (int)ft_strlen(a.comment))
			out_file->content[out_file->total_size] = a.comment[i];
		else
			out_file->content[out_file->total_size] = 0;
		out_file->total_size += 1;
		i++;
	}
*/
	/*
	** NULL AGAIN
	*/
/*
	i = 0;
	while (i < 4)
	{
		out_file->content[out_file->total_size] = 0;
		out_file->total_size += 1;
		i++;
	}
*/
	/*
	** CODE
	*/
/*
	while (a.label_list)
	{
	
		a.label_list
	}
*/	///////////////////////////////////////////////////////////////////////
	return (TRUE);
}
