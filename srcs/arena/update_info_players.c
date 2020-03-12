/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info_players.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:52:22 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:01:06 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		update_info_players3(t_disp *d, t_arena a, char *info, int i)
{
	int		ph;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	d->mod.y = (ph * i) + 1 + d->players.y + (ph / 9) * 5;
	d->mod.w = (d->players.w / 2) - 18;
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(update_visu.c) SDL_RenderFillRect : ", d);
	info = ft_itoa(a.champion_table[i].lives_since_last_check);
	disp_ttf(info, d->color, d);
	free(info);
	d->mod.y = (ph * i) + d->players.y + (ph - (ph / 10) - 15) + 1;
	d->mod.x = d->players.x + 6;
	d->mod.w = d->players.w - 12;
	d->mod.h = 8 + (ph / 10);
	if (SDL_SetRenderDrawColor(d->rend, 50, 50, 50, 250) < 0)
		error("(update_visu.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(update_visu.c) SDL_RenderFillRect : ", d);
	d->mod.w = ((d->players.w - 12) * a.champion_table[i].total_process)
		/ a.total_process_nb;
	if (SDL_SetRenderDrawColor(d->rend,
	(d->color_champ[a.champion_table[i].number] & 0xFF000000) >> 24,
	(d->color_champ[a.champion_table[i].number] & 0xFF0000) >> 16,
	(d->color_champ[a.champion_table[i].number] & 0xFF00) >> 8, 150) < 0)
		error("(update_visu.c) SDL_SetRenderDrawColor : ", d);
}

void		update_info_players2(t_disp *d, t_arena a, char *info, int i)
{
	int		ph;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(update_visu.c) SDL_SetRenderDrawColor : ", d);
	d->mod.h = 8 + (ph / 10);
	d->mod.x = d->players.x + (d->players.w / 2) + 15;
	d->mod.y = (ph * i) + d->players.y + (ph / 9) * 3 + 1;
	d->mod.w = (d->players.w / 2) - 18;
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(update_visu.c) SDL_RenderDrawRect : ", d);
	d->mod.y = (ph * i) + d->players.y + (ph / 9.5) * 3;
	info = ft_itoa(a.champion_table[i].total_memory_owned);
	disp_ttf(info, d->color, d);
	d->mod.x += ft_strlen(info) * (ph / 9);
	free(info);
	disp_ttf("(", d->color, d);
	info = ft_itoa(100 * a.champion_table[i].total_memory_owned / 4096);
	d->mod.x += ph / 8;
	disp_ttf(info, d->color, d);
	d->mod.x += ft_strlen(info) * (ph / 9);
	free(info);
	disp_ttf(" %)", d->color, d);
	d->mod.h = 8 + (ph / 10);
	d->mod.x = d->players.x + (d->players.w / 2) + 15;
}

void		update_info_players(t_disp *d, t_arena a, char *info, int i)
{
	int		ph;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", ph / 7.2))))
		error("(update_visu.c) TTF_OpenFont : ", d);
	while (i < a.nb_champs)
	{
		update_info_players2(d, a, info, i);
		update_info_players3(d, a, info, i);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(update_visu.c) SDL_RenderFillRect : ", d);
		i++;
	}
}
