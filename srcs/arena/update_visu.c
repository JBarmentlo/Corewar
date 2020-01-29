/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:34:21 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/27 11:27:45 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		update_visu(t_disp *d, t_arena a)
{
	int			i;
	char		hex[2];
	SDL_Color	color;

	i = 0;
	color.a = 0;
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->b_tmp, NULL, &d->arena) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	TTF_CloseFont(d->font1);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 22))))
		error("(menu.c) TTF_OpenFont : ", d);
	hex[1] = '\0';
	while (i < MEM_SIZE)
	{
		color.r = (d->color_champ[a.memory_color[i]] & 0xFF000000) >> 24;
		color.g = (d->color_champ[a.memory_color[i]] & 0xFF0000) >> 16;
		color.b = (d->color_champ[a.memory_color[i]] & 0xFF00) >> 8;
		hex[0] = (a.memory[i] >> 4) + '0';
		d->mod.x = d->arena.x + 10 + 29.7 * (i % 64);
		d->mod.y = d->arena.y + 14 + 21.4 * (i / 64);
		d->mod.h = 21;
		d->mod.w = 14;
		disp_ttf(hex, color, d);
		hex[0] = (a.memory[i] & 0x0F) + '0';
		d->mod.x = d->arena.x + 23 + 29.7 * (i % 64);
		d->mod.w = 14;
		disp_ttf(hex, color, d);
		i++;
	}
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, &d->arena, &d->arena) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
/*
	d->mod.x = d->process.x + 55 + (13 * 15);
	d->mod.h = 30;
	d->mod.w = 300;
	i = 0;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	while (i < 4)
	{
		d->mod.y = d->process.y + 15 + (60 * i);
		if (SDL_RenderCopy(d->rend, d->f_tmp, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		if (i == 0)
			disp_ttf(ft_itoa(a.cycle_to_die), color, d);
		if (i == 1)
			disp_ttf(ft_itoa(a.max_checks), color, d);
		if (i == 2)
			disp_ttf(ft_itoa(a.total_live_since_check), color, d);
		if (i == 3)
			disp_ttf(hex, color, d);

		i++;
	}
	d->mod.x = 1980;
	d->mod.y = d->process.h + 20 - (d->process.h / 3);
	d->mod.w = 540;
	d->mod.h = (d->process.h / 3) - 20;
	i = 0;
	while (a.process_table[i] != NULL && i < 10)
	{
		color.r = (d->color_champ[a.process_table[i]->owner->number] & 0xFF000000) >> 24;
		color.g = (d->color_champ[a.process_table[i]->owner->number] & 0xFF0000) >> 16;
		color.b = (d->color_champ[a.process_table[i]->owner->number] & 0xFF00) >> 8;
		disp_ttf(ft_itoa(a.process_table[i]->carry), color, d);
		d->mod.x += 20;
		i++;
	}
*/
	SDL_RenderPresent(d->rend);
}
