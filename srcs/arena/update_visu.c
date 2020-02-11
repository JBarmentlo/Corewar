/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:34:21 by ncoursol          #+#    #+#             */
/*   Updated: 2020/02/04 16:55:47 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

size_t		ft_nbrlen(int nbr)
{
	int		len;

	len = 0;
	if (nbr == 0)
		return (1);
	if (nbr < len)
		len += 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa2(int n)
{
	size_t	i;
	size_t	n_size;
	char	*str;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	n_size = ft_nbrlen(n);
	str = (char *)malloc(sizeof(char) * (n_size + 1));
	if (str == 0)
		return (0);
	str[n_size] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i += 1;
	}
	while (i < n_size--)
	{
		str[n_size] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

void		update_visu(t_disp *d, t_arena a)
{
	int			i;
	char		hex[3];
	char		*info;
	SDL_Color	color;
	int			ph;
	t_process	*first;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	i = 0;
	color.a = 0;
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->b_tmp, NULL, &d->arena) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	TTF_CloseFont(d->font1);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 32))))
		error("(menu.c) TTF_OpenFont : ", d);
	hex[2] = '\0';
	///////////////////ARENA/////////////////////////
	while (i < MEM_SIZE)
	{
		color.r = (d->color_champ[a.memory_color[i] - '0'] & 0xFF000000) >> 24;
		color.g = (d->color_champ[a.memory_color[i] - '0'] & 0xFF0000) >> 16;
		color.b = (d->color_champ[a.memory_color[i] - '0'] & 0xFF00) >> 8;
		hex[0] = (a.memory[i] >> 4) + '0';
		hex[0] = (hex[0] > '9' ? hex[0] + 7 : hex[0]);
		d->mod.x = d->arena.x + 10 + 29.7 * (i % 64);
		d->mod.y = d->arena.y + 14 + 21.4 * (i / 64);
		d->mod.h = 24;
		d->mod.w = 24;
		hex[1] = (a.memory[i] & 0x0F) + '0';
		hex[1] = (hex[1] > '9' ? hex[1] + 7 : hex[1]);
		d->txt = TTF_RenderText_Solid(d->font1, hex, color);
		d->font = SDL_CreateTextureFromSurface(d->rend, d->txt);
		if (SDL_RenderCopy(d->rend, d->font, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		SDL_DestroyTexture(d->font);
		SDL_FreeSurface(d->txt);
		i++;
	}
	d->mod.h = 21;
	d->mod.w = 26;
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	first = a.process_list;
	while (a.process_list)
	{
		if (SDL_SetRenderDrawColor(d->rend, (d->color_champ[a.process_list->owner->number] & 0xFF000000) >> 24, (d->color_champ[a.process_list->owner->number] & 0xFF0000) >> 16, (d->color_champ[a.process_list->owner->number] & 0xFF00) >> 8, 150) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		d->mod.x = d->arena.x + 10 + 29.7 * (a.process_list->PC % 64);
		d->mod.y = d->arena.y + 14 + 21.4 * (a.process_list->PC / 64);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderFillRect : ", d);
		a.process_list = a.process_list->next_list;
	}
	a.process_list = first;
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	//////////////////INFO GLOBAL///////////////////////
	d->mod.h = 30;
	i = 0;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	while (i < 4)
	{
		d->mod.w = 300;
		d->mod.y = d->process.y + 15 + (60 * i);
		d->mod.x = d->process.x + 55 + (13 * 15);
		if (SDL_RenderCopy(d->rend, d->p_tmp, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		d->mod.x += 5;
		if (i == 0)
		{
			d->mod.w = ft_nbrlen(CYCLE_TO_DIE) * 20;
			info = ft_itoa2(CYCLE_TO_DIE);
			disp_ttf(info, color, d);
			free(info);
		}
		else if (i == 1)
		{
			d->mod.w = ft_nbrlen(CYCLE_DELTA) * 20;
			info = ft_itoa2(CYCLE_DELTA);
			disp_ttf(info, color, d);
			free(info);
		}
		else if (i == 2)
		{
			d->mod.w = ft_nbrlen(NBR_LIVE) * 20;
			info = ft_itoa2(NBR_LIVE);
			disp_ttf(info, color, d);
			free(info);
		}
		else if (i == 3)
		{
			d->mod.w = ft_nbrlen(4) * 20;
			info = ft_itoa2(4);
			disp_ttf(info, color, d);
			free(info);
		}
		i++;
	}
	////////////////////INFO PLAYERS//////////////////////
	i = 1;
	d->mod.x = d->players.x + (d->players.w / 2) + 15;
	d->mod.h = 10 + (ph / 10);
	while (i <= a.nb_champs)
	{
		d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 9) * 3;
		info = ft_itoa(a.champion_table[i - 1].total_memory_owned);
		d->mod.w = ft_nbrlen(a.champion_table[i - 1].total_memory_owned) * 15;
		disp_ttf(info, color, d);
		free(info);
		d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 9) * 5;
		info = ft_itoa(a.champion_table[i - 1].lives_since_last_check);
		d->mod.w = ft_nbrlen(a.champion_table[i - 1].lives_since_last_check) * 15;
		disp_ttf(info, color, d);
		free(info);
		i++;
	}
	/////////////////FCT LIST////////////////////////
	d->mod.x = 1980;
	d->mod.y = 880 + 20 - (880 / 3);
	d->mod.w = 540;
	d->mod.h = (880 / 3) - 20;
	if (SDL_RenderCopy(d->rend, d->f_tmp, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	d->mod.y = 880 + 27 - (880 / 3);
	while (a.process_list)
	{
	//	printf("op : [%s][%s] cycle : [%u]\n", a.process_list->owner->header.prog_name, a.process_list->current_op->name, a.process_list->current_op->cycle_to_wait);
		if (a.process_list->current_op)
		{
			color.r = (d->color_champ[a.process_list->owner->number] & 0xFF000000) >> 24;
			color.g = (d->color_champ[a.process_list->owner->number] & 0xFF0000) >> 16;
			color.b = (d->color_champ[a.process_list->owner->number] & 0xFF00) >> 8;
	//		printf("r : [%d] g : [%d] b : [%d]\n", color.r, color.g, color.b);
			d->mod.h = 20;
			d->mod.x = 1995;
			d->mod.w = ft_strlen(a.process_list->owner->header.prog_name) * 15;
			disp_ttf(a.process_list->owner->header.prog_name, color, d);
			d->mod.x += 15 + d->mod.w;
			d->mod.w = ft_strlen(a.process_list->current_op->name) * 15;
			disp_ttf(a.process_list->current_op->name, color, d);
			d->mod.x += 15 + d->mod.w;	
			d->mod.w = ft_nbrlen(a.process_list->current_op->cycle_to_wait) * 15;
			disp_ttf(ft_itoa2(a.process_list->current_op->cycle_to_wait), color, d);
			d->mod.y += 20;	
		}
		a.process_list = a.process_list->next_list;
	}
	///////////////////////////////////////////////
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
}
