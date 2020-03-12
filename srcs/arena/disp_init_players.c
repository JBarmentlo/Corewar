/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_init_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:07:12 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:05:00 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void			disp_init_players2(t_disp *d, int i, int ph, char *nb_p)
{
	if (!((d->font1 = TTF_OpenFont("img/font1.ttf", 65))))
		error("(disp_init_players.c) TTF_OpenFont : ", d);
	if (SDL_RenderDrawLine(d->rend, d->players.x, (ph * i) + d->players.y,
				(d->players.x + d->players.w), (ph * i) + d->players.y) < 0)
		error("(disp_init_players.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, d->players.x,
				d->players.y + 70 + (ph * (i - 1)), d->players.x + 70,
				d->players.y + 70 + (ph * (i - 1))) < 0)
		error("(disp_init_players.c) SDL_RenderDrawLine : ", d);
	if (SDL_RenderDrawLine(d->rend, d->players.x + 70,
				d->players.y + (ph * (i - 1)), d->players.x + 70,
				d->players.y + 70 + (ph * (i - 1))) < 0)
		error("(disp_init_players.c) SDL_RenderDrawLine : ", d);
	if (i == 1)
		d->color_champ[i] = 0xFF000000;
	else if (i == 2)
		d->color_champ[i] = 0xFFFF0000;
	else if (i == 3)
		d->color_champ[i] = 0x00FF0000;
	else if (i == 4)
		d->color_champ[i] = 0x0000FF00;
	d->color.r = (d->color_champ[i] & 0xFF000000) >> 24;
	d->color.g = (d->color_champ[i] & 0xFF0000) >> 16;
	d->color.b = (d->color_champ[i] & 0xFF00) >> 8;
	nb_p[1] = i + '0';
}

void			disp_init_players3(t_disp *d, int i, int ph, char *nb_p)
{
	d->mod.x = d->players.x + 5;
	d->mod.y = (ph * (i - 1)) + d->players.y + 5;
	disp_ttf(nb_p, d->color, d);
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph - (ph / 10) - 15);
	d->mod.h = 10 + (ph / 10);
	d->mod.w = d->players.w - 10;
	if (SDL_SetRenderDrawColor(d->rend, 50, 50, 50, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", ph / 5.5))))
		error("(disp_init_players.c) TTF_OpenFont : ", d);
	d->mod.x = d->players.x + 120;
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 10);
	disp_ttf("name", d->color, d);
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 10) * 3;
	disp_ttf("area", d->color, d);
}

void			disp_init_players4(t_disp *d, int i, int ph)
{
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 10) * 5;
	disp_ttf("lives", d->color, d);
	d->mod.x = d->players.x + (d->players.w / 2) + 10;
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 9);
	d->mod.h = 10 + (ph / 10);
	d->mod.w = (d->players.w / 2) - 15;
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 9) * 3;
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 9) * 5;
}

void			disp_init_players5(t_disp *d, t_arena a, int i, int ph)
{
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->mod) < 0)
		error("(disp_init_players.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp_init_players.c) SDL_SetRenderDrawColor : ", d);
	d->mod.y = (ph * (i - 1)) + d->players.y + (ph / 13);
	if (ft_strlen(a.champion_table[i - 1].header.prog_name) > 18)
	{
		a.champion_table[i - 1].header.prog_name[15] = '.';
		a.champion_table[i - 1].header.prog_name[16] = '.';
		a.champion_table[i - 1].header.prog_name[17] = '.';
		a.champion_table[i - 1].header.prog_name[18] = '\0';
	}
	if (a.nb_champs != 4)
	{
		d->mod.y += (a.nb_champs == 2 ? 5 : 3);
		TTF_CloseFont(d->font1);
		d->font1 = NULL;
		if (!((d->font1 = TTF_OpenFont("img/font2.ttf",
		ph / ((a.nb_champs == 2 ? 8.7 : 5.7))))))
			error("(disp_init_players.c) TTF_OpenFont : ", d);
	}
}

void			disp_init_players(t_disp *d, t_arena a)
{
	int		i;
	char	nb_p[3];
	int		ph;

	i = 1;
	nb_p[2] = '\0';
	nb_p[0] = 'P';
	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	while (i <= a.nb_champs)
	{
		disp_init_players2(d, i, ph, nb_p);
		disp_init_players3(d, i, ph, nb_p);
		disp_init_players4(d, i, ph);
		disp_init_players5(d, a, i, ph);
		d->mod.x += 5;
		d->color.r = 255;
		d->color.g = 255;
		d->color.b = 255;
		disp_ttf(a.champion_table[i - 1].header.prog_name, d->color, d);
		i++;
		TTF_CloseFont(d->font1);
		d->font1 = NULL;
	}
}
