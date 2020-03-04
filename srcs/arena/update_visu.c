/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:34:21 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/02 18:20:20 by ncoursol         ###   ########.fr       */
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

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	i = 0;
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->b_tmp, NULL, &d->arena) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 22))))
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
	i = 0;
	while (a.process_table[i] != NULL)
	{
		if (SDL_SetRenderDrawColor(d->rend, (d->color_champ[a.process_table[i]->owner->number] & 0xFF000000) >> 24, (d->color_champ[a.process_table[i]->owner->number] & 0xFF0000) >> 16, (d->color_champ[a.process_table[i]->owner->number] & 0xFF00) >> 8, 110) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		d->mod.x = d->arena.x + 10 + 29.7 * (a.process_table[i]->PC % 64);
		d->mod.y = d->arena.y + 14 + 21.4 * (a.process_table[i]->PC / 64);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderFillRect : ", d);
		i++;
	}
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	//////////////////INFO GLOBAL///////////////////////
	d->mod.h = 30;
	i = 0;
	d->color.r = 255;
	d->color.g = 255;
	d->color.b = 255;
	while (i < 5)
	{
		d->mod.w = 300;
		d->mod.y = d->process.y + 15 + (60 * i);
		d->mod.x = d->process.x + 55 + (13 * 15);
		if (SDL_RenderCopy(d->rend, d->p_tmp, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		d->mod.x += 5;
		if (i == 0)
		{
			d->mod.w = ft_nbrlen(a.cycle_to_die) * 20;
			info = ft_itoa2(a.cycle_to_die);
			disp_ttf(info, d->color, d);
			free(info);
		}
		else if (i == 1)
		{
			d->mod.w = ft_nbrlen(CYCLE_DELTA) * 20;
			info = ft_itoa2(CYCLE_DELTA);
			disp_ttf(info, d->color, d);
			free(info);
		}
		else if (i == 2)
		{
			d->mod.w = ft_nbrlen(a.total_live_since_check) * 20;
			info = ft_itoa2(a.total_live_since_check);
			disp_ttf(info, d->color, d);
			free(info);
		}
		else if (i == 3)
		{
			d->mod.w = ft_nbrlen(a.total_process_nb) * 20;
			info = ft_itoa2(a.total_process_nb);
			disp_ttf(info, d->color, d);
			free(info);
		}
		else if (i == 4)
		{
			d->mod.w = ft_nbrlen(a.cycle % a.cycle_to_die) * 20;
			info = ft_itoa2(a.cycle % a.cycle_to_die);
			disp_ttf(info, d->color, d);
			free(info);
			d->mod.x += d->mod.w;
			d->mod.w = 40;
			disp_ttf(" (", d->color, d);
			d->mod.x += 40;
			d->mod.w = ft_nbrlen(d->delay * 10) * 20;
			info = ft_itoa2(d->delay * 10);
			disp_ttf(info, d->color, d);
			free(info);
			d->mod.x += d->mod.w;
			d->mod.w = 100;
			disp_ttf(".cps)", d->color, d);
		}
		i++;
	}
	////////////////////INFO PLAYERS//////////////////////
	i = 0;
	while (i < a.nb_champs)
	{
		if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		d->mod.x = d->players.x + (d->players.w / 2) + 14;
		d->mod.h = 8 + (ph / 10);
		d->mod.y = (ph * i) + d->players.y + (ph / 9) * 3 + 1;
		d->mod.w = (d->players.w / 2) - 17;
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);
		info = ft_itoa(a.champion_table[i].total_memory_owned);
		d->mod.w = ft_nbrlen(a.champion_table[i].total_memory_owned) * 15;
		disp_ttf(info, d->color, d);
		free(info);
		d->mod.x += d->mod.w;
		d->mod.w = 30;
		disp_ttf(" (", d->color, d);
		info = ft_itoa(100 * a.champion_table[i].total_memory_owned / 4096);
		d->mod.x += 30;
		d->mod.w = ft_nbrlen(100 * a.champion_table[i].total_memory_owned / 4096) * 15;
		disp_ttf(info, d->color, d);
		free(info);
		d->mod.x += d->mod.w;
		d->mod.w = 45;
		disp_ttf(" %)", d->color, d);

		d->mod.x = d->players.x + (d->players.w / 2) + 14;
		d->mod.y = (ph * i) + 1 + d->players.y + (ph / 9) * 5;
		d->mod.w = (d->players.w / 2) - 17;
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);
		info = ft_itoa(a.champion_table[i].lives_since_last_check);
		d->mod.w = ft_nbrlen(a.champion_table[i].lives_since_last_check) * 15;
		disp_ttf(info, d->color, d);
		free(info);

		d->mod.y = (ph * i) + d->players.y + (ph - (ph / 10) - 15) + 1;
		d->mod.h = 8 + (ph / 10);
		d->mod.x = d->players.x + 6;
		d->mod.w = d->players.w - 12;
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
	d->mod.x = 1980;
	d->mod.y = 880 + 20 - (880 / 3);
	d->mod.w = 540;
	d->mod.h = (880 / 3) - 20;
	if (SDL_RenderCopy(d->rend, d->f_tmp, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	d->mod.y = 880 + 27 - (880 / 3);
	i = 0;
	while (a.process_table[i])
	{
		if (a.process_table[i]->current_op)
		{
			d->color.r = (d->color_champ[a.process_table[i]->owner->number] & 0xFF000000) >> 24;
			d->color.g = (d->color_champ[a.process_table[i]->owner->number] & 0xFF0000) >> 16;
			d->color.b = (d->color_champ[a.process_table[i]->owner->number] & 0xFF00) >> 8;
			d->mod.h = 20;
			d->mod.x = 1995;
			if (ft_strlen(a.process_table[i]->owner->header.prog_name) > 16)
			{
				a.process_table[i]->owner->header.prog_name[13] = '.';
				a.process_table[i]->owner->header.prog_name[14] = '.';
				a.process_table[i]->owner->header.prog_name[15] = '.';
				a.process_table[i]->owner->header.prog_name[16] = '\0';
			}
			d->mod.w = ft_strlen(a.process_table[i]->owner->header.prog_name) * 15;
			disp_ttf(a.process_table[i]->owner->header.prog_name, d->color, d);
			d->mod.x += 15 + d->mod.w;
			d->mod.w = ft_strlen(a.process_table[i]->current_op->name) * 15;
			disp_ttf(a.process_table[i]->current_op->name, d->color, d);
			d->mod.x += 15 + d->mod.w;	
			d->mod.w = ft_nbrlen(a.process_table[i]->current_op->cycle_to_wait) * 15;
			info = ft_itoa2(a.process_table[i]->current_op->cycle_to_wait);
			disp_ttf(info, d->color, d);
			free(info);
			d->mod.y += 20;	
		}
		i++;
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
