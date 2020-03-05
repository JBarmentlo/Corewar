/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:34:21 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/04 13:31:12 by ncoursol         ###   ########.fr       */
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
	int			ph;
	t_process	*first;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	i = 0;
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->b_tmp, NULL, &d->arena) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 19))))
		error("(menu.c) TTF_OpenFont : ", d);
	hex[2] = '\0';
	///////////////////ARENA/////////////////////////
	d->s_arena = SDL_CreateRGBSurface(0, d->screen.w, d->screen.h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	while (i < MEM_SIZE)
	{
		d->color.r = (d->color_champ[a.memory_color[i] - '0'] & 0xFF000000) >> 24;
		d->color.g = (d->color_champ[a.memory_color[i] - '0'] & 0xFF0000) >> 16;
		d->color.b = (d->color_champ[a.memory_color[i] - '0'] & 0xFF00) >> 8;
		hex[0] = (a.memory[i] >> 4) + '0';
		hex[0] = (hex[0] > '9' ? hex[0] + 7 : hex[0]);
		hex[1] = (a.memory[i] & 0x0F) + '0';
		hex[1] = (hex[1] > '9' ? hex[1] + 7 : hex[1]);
		d->mod.x = d->arena.x + 10 + 29.7 * (i % 64);
		d->mod.y = d->arena.y + 14 + 21.4 * (i / 64);
		d->txt = TTF_RenderText_Solid(d->font1, hex, d->color);
		SDL_BlitSurface(d->txt, NULL, d->s_arena, &d->mod);
		SDL_FreeSurface(d->txt);
		i++;
	}
	d->font = SDL_CreateTextureFromSurface(d->rend, d->s_arena);
	if (SDL_RenderCopy(d->rend, d->font, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	SDL_DestroyTexture(d->font);
	SDL_FreeSurface(d->s_arena);
	d->mod.h = 21;
	d->mod.w = 26;
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	first = a.process_list;
	while (a.process_list != NULL)
	{
		if (SDL_SetRenderDrawColor(d->rend, (d->color_champ[a.process_list->owner->number] & 0xFF000000) >> 24, (d->color_champ[a.process_list->owner->number] & 0xFF0000) >> 16, (d->color_champ[a.process_list->owner->number] & 0xFF00) >> 8, 110) < 0)
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
	TTF_CloseFont(d->font1);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 30))))
		error("(menu.c) TTF_OpenFont : ", d);
	i = 0;
	d->color.r = 255;
	d->color.g = 255;
	d->color.b = 255;
	d->mod.h = 30;
	while (i < 5)
	{
		d->mod.y = d->process.y + 15 + (60 * i);
		d->mod.x = d->process.x + 55 + (13 * 15);
		d->mod.w = 300;
		if (SDL_RenderCopy(d->rend, d->p_tmp, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		d->mod.x += 5;
		if (i == 0)
			info = ft_itoa2(a.cycle_to_die);
		else if (i == 1)
			info = ft_itoa2(CYCLE_DELTA);
		else if (i == 2)
			info = ft_itoa2(a.total_live_since_check);
		else if (i == 3)
			info = ft_itoa2(a.total_process_nb);
		else if (i == 4)
		{
			info = ft_itoa2(a.cycle % a.cycle_to_die);
			disp_ttf(info, d->color, d);
			free(info);
			d->mod.x += ft_strlen(ft_itoa2(a.cycle % a.cycle_to_die)) * 18;
			disp_ttf(" (", d->color, d);
			d->mod.x += 15;
			info = ft_itoa2(d->delay * 10);
			disp_ttf(info, d->color, d);
			free(info);
			d->mod.x += ft_strlen(ft_itoa2(d->delay * 10)) * 20;
			disp_ttf(".cps)", d->color, d);
		}
		if (i < 4)
		{
			disp_ttf(info, d->color, d);
			free(info);
		}
		i++;
	}
	////////////////////INFO PLAYERS//////////////////////
	i = 0;
	TTF_CloseFont(d->font1);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", ph / 7.2))))
		error("(menu.c) TTF_OpenFont : ", d);
	while (i < a.nb_champs)
	{
		if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		d->mod.h = 8 + (ph / 10);
		d->mod.x = d->players.x + (d->players.w / 2) + 15;
		d->mod.y = (ph * i) + d->players.y + (ph / 9) * 3 + 1;
		d->mod.w = (d->players.w / 2) - 18;
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);
		d->mod.y = (ph * i) + d->players.y + (ph / 9.5) * 3;
		info = ft_itoa(a.champion_table[i].total_memory_owned);
		disp_ttf(info, d->color, d);
		free(info);
		d->mod.x += ft_strlen(ft_itoa(a.champion_table[i].total_memory_owned)) * (ph / 8);
		disp_ttf("(", d->color, d);
		info = ft_itoa(100 * a.champion_table[i].total_memory_owned / 4096);
		d->mod.x += ph / 8;
		disp_ttf(info, d->color, d);
		free(info);
		d->mod.x += ft_strlen(ft_itoa(100 * a.champion_table[i].total_memory_owned / 4096)) * 15;
		disp_ttf(" %)", d->color, d);
		d->mod.h = 8 + (ph / 10);
		d->mod.x = d->players.x + (d->players.w / 2) + 15;
		d->mod.y = (ph * i) + 1 + d->players.y + (ph / 9) * 5;
		d->mod.w = (d->players.w / 2) - 18;
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);
		info = ft_itoa(a.champion_table[i].lives_since_last_check);
		disp_ttf(info, d->color, d);
		free(info);
		d->mod.y = (ph * i) + d->players.y + (ph - (ph / 10) - 15) + 1;
		d->mod.x = d->players.x + 6;
		d->mod.w = d->players.w - 12;
		d->mod.h = 8 + (ph / 10);
		if (SDL_SetRenderDrawColor(d->rend, 50, 50, 50, 250) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);
		d->mod.w = ((d->players.w - 12) * a.champion_table[i].total_process) / a.total_process_nb;
		if (SDL_SetRenderDrawColor(d->rend, (d->color_champ[a.champion_table[i].number] & 0xFF000000) >> 24, (d->color_champ[a.champion_table[i].number] & 0xFF0000) >> 16, (d->color_champ[a.champion_table[i].number] & 0xFF00) >> 8, 150) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);

		i++;
	}
	/////////////////FCT LIST////////////////////////
	TTF_CloseFont(d->font1);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 18))))
		error("(menu.c) TTF_OpenFont : ", d);
	d->mod.x = 1980;
	d->mod.y = 880 + 20 - (880 / 3);
	d->mod.w = 540;
	d->mod.h = (880 / 3) - 20;
	if (SDL_RenderCopy(d->rend, d->f_tmp, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	d->mod.y = 880 + 27 - (880 / 3);
	i = 0;
	while (a.process_list && i < 17)
	{
		if (a.process_list->current_op)
		{
			d->color.r = (d->color_champ[a.process_list->owner->number] & 0xFF000000) >> 24;
			d->color.g = (d->color_champ[a.process_list->owner->number] & 0xFF0000) >> 16;
			d->color.b = (d->color_champ[a.process_list->owner->number] & 0xFF00) >> 8;
			d->mod.x = 1995;
			if (ft_strlen(a.process_list->owner->header.prog_name) > 18)
			{
				a.process_list->owner->header.prog_name[15] = '.';
				a.process_list->owner->header.prog_name[16] = '.';
				a.process_list->owner->header.prog_name[17] = '.';
				a.process_list->owner->header.prog_name[18] = '\0';
			}
			disp_ttf(a.process_list->owner->header.prog_name, d->color, d);
			d->mod.x += 15 + d->mod.w;
			disp_ttf(a.process_list->current_op->name, d->color, d);
			d->mod.x += 15 + d->mod.w;	
			info = ft_itoa2(a.process_list->current_op->cycle_to_wait);
			disp_ttf(info, d->color, d);
			free(info);
			d->mod.y += 15;
			i++;
		}
		a.process_list = a.process_list->next_list;
	}
	///////////////////////////////////////////////
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
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
