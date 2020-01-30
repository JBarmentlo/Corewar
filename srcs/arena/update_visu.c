/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:34:21 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/30 18:29:06 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		update_visu(t_disp *d, t_arena a)
{
	int			i;
	char		hex[3];
	SDL_Color	color;
	int			ph;
 
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
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	//////////////////INFO GLOBAL///////////////////////
	d->mod.x = d->process.x + 55 + (13 * 15);
	d->mod.h = 30;
	d->mod.w = 300;
	i = 0;
	while (i < 4)
	{
		d->mod.y = d->process.y + 15 + (60 * i);
		if (SDL_RenderCopy(d->rend, d->p_tmp, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		i++;
	}
	////////////////////INFO PLAYERS//////////////////////
	i = 1;
	d->mod.x = d->players.x + 5;
	d->mod.h = 30;
	d->mod.w = d->players.w - 10;
	while (i <= a.nb_champs)
	{
		d->mod.y = (ph * (i - 1)) + d->players.y + (ph - 35);
		i++;
	}
	/////////////////FCT LIST////////////////////////
	color.r = 255;
	color.g = 255;
	color.b = 255;
/*		d->mod.x = 1980;
		d->mod.y = d->process.h + 20 - (d->process.h / 3);
		d->mod.w = 540;
		d->mod.h = (d->process.h / 3) - 20;
		i = 0;
		while (a.process_table[i] != NULL && i < 10)
		{
		color.r = (d->color_champ[a.process_table[i + 1]->owner->number] & 0xFF000000) >> 24;
		color.g = (d->color_champ[a.process_table[i + 1]->owner->number] & 0xFF0000) >> 16;
		color.b = (d->color_champ[a.process_table[i + 1]->owner->number] & 0xFF00) >> 8;
		disp_ttf(ft_itoa(a.process_table[i]->carry), color, d);
		d->mod.x += 20;
		i++;
		}
*/	////////////////////////////////////////////////
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, &d->arena, &d->arena) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
}
