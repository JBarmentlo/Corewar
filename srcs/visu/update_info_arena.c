/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info_arena.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 17:22:31 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:36:43 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		update_arena3(t_disp *d, t_arena a, t_process *first)
{
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(update_visu.c) SDL_SetRenderDrawBlendMode error : ", d);
	first = a.process_list;
	while (a.process_list != NULL)
	{
		if (SDL_SetRenderDrawColor(d->rend,
		(d->color_champ[a.process_list->owner->number] & 0xFF000000) >> 24,
		(d->color_champ[a.process_list->owner->number] & 0xFF0000) >> 16,
		(d->color_champ[a.process_list->owner->number] & 0xFF00) >> 8, 110) < 0)
			error("(update_visu.c) SDL_SetRenderDrawColor : ", d);
		d->mod.x = d->arena.x + 10 + 29.7 * (a.process_list->pc % 64);
		d->mod.y = d->arena.y + 14 + 21.4 * (a.process_list->pc / 64);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(update_visu.c) SDL_RenderFillRect : ", d);
		a.process_list = a.process_list->next_list;
	}
	a.process_list = first;
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(update_visu.c) SDL_SetRenderDrawBlendMode error : ", d);
}

void		update_arena2(t_disp *d, t_arena a, int i)
{
	char		hex[3];

	hex[2] = '\0';
	while (i < MEM_SIZE)
	{
		d->color.r = (d->color_champ[a.memory_color[i] - '0']
		& 0xFF000000) >> 24;
		d->color.g = (d->color_champ[a.memory_color[i] - '0'] & 0xFF0000) >> 16;
		d->color.b = (d->color_champ[a.memory_color[i] - '0'] & 0xFF00) >> 8;
		hex[0] = (a.memory[i] >> 4) + '0';
		hex[0] = (hex[0] > '9' ? hex[0] + 7 : hex[0]);
		hex[1] = (a.memory[i] & 0x0F) + '0';
		hex[1] = (hex[1] > '9' ? hex[1] + 7 : hex[1]);
		d->mod.x = d->arena.x + 10 + 29.7 * (i % 64);
		d->mod.y = d->arena.y + 14 + 21.4 * (i / 64);
		if ((d->txt = TTF_RenderText_Solid(d->font1, hex, d->color)) == NULL)
			error("(update_visu.c) TTF_RenderText_Solid : ", d);
		if (SDL_BlitSurface(d->txt, NULL, d->s_arena, &d->mod) < 0)
			error("(update_visu.c) SDL_BlitSurface : ", d);
		SDL_FreeSurface(d->txt);
		d->txt = NULL;
		i++;
	}
}

void		update_arena(t_disp *d, t_arena a, int i)
{
	t_process	*first;

	first = NULL;
	if ((d->s_arena = SDL_CreateRGBSurface(0, d->screen.w, d->screen.h,
	32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff)) == NULL)
		error("(update_visu.c) SDL_CreateRGBSurface : ", d);
	update_arena2(d, a, i);
	if ((d->font = SDL_CreateTextureFromSurface(d->rend, d->s_arena)) == NULL)
		error("(update_visu.c) SDL_CreateTextureFromSurface : ", d);
	SDL_FreeSurface(d->s_arena);
	d->s_arena = NULL;
	if (SDL_RenderCopy(d->rend, d->font, NULL, NULL) < 0)
		error("(update_visu.c) SDL_RenderCopy : ", d);
	SDL_DestroyTexture(d->font);
	d->font = NULL;
	d->mod.h = 21;
	d->mod.w = 26;
	update_arena3(d, a, first);
}
