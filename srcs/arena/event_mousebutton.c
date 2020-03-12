/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mousebutton.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:59:26 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:38:10 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		event_button_players(t_disp *d, int i, int j)
{
	if (j == 0)
		d->color_champ[i + 1] = 0xFF000000;
	else if (j == 1)
		d->color_champ[i + 1] = 0xFFFF0000;
	else if (j == 2)
		d->color_champ[i + 1] = 0x00FF0000;
	else if (j == 3)
		d->color_champ[i + 1] = 0x0000FF00;
	else if (j == 4)
		d->color_champ[i + 1] = 0xFF00FF00;
	else if (j == 5)
		d->color_champ[i + 1] = 0x00000000;
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(event_mousebutton.c) SDL_SetRenderTarget : ", d);
	if (!((d->font1 = TTF_OpenFont("img/font1.ttf", 65))))
		error("(event_mousebutton.c) TTF_OpenFont : ", d);
	d->color.r = (d->color_champ[i + 1] & 0xFF000000) >> 24;
	d->color.g = (d->color_champ[i + 1] & 0xFF0000) >> 16;
	d->color.b = (d->color_champ[i + 1] & 0xFF00) >> 8;
}

void		event_button_players2(t_disp *d, int i, int ph, t_arena a)
{
	char	p[3];

	p[0] = 'P';
	p[1] = (i + 1) + '0';
	p[2] = '\0';
	d->mod.x = d->players.x + 5;
	d->mod.y = (ph * i) + d->players.y + 5;
	disp_ttf(p, d->color, d);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", ph / 5.5))))
		error("(event_mousebutton.c) TTF_OpenFont : ", d);
	d->mod.x = d->players.x + 120;
	d->mod.y = (ph * i) + d->players.y + (ph / 10);
	disp_ttf("name", d->color, d);
	d->mod.y = (ph * i) + d->players.y + (ph / 10) * 3;
	disp_ttf("area", d->color, d);
	d->mod.y = (ph * i) + d->players.y + (ph / 10) * 5;
	disp_ttf("lives", d->color, d);
	d->mod.y = (ph * i) + d->players.y + (ph - (ph / 10) - 15) + 1;
	d->mod.h = 8 + (ph / 10);
	d->mod.w = d->players.w - 12;
	d->mod.x = d->players.x + 6;
	event_button_players3(d, i, a);
}

void		event_button_bar2(t_disp *d, int i, int *timeout, int *running)
{
	if (i == 0)
		d->delay = (d->delay >= 100 ? 100 : d->delay + 4);
	else if (i == 1)
		d->delay = (d->delay <= 10 ? 10 : d->delay - 4);
	else if (i == 2)
		d->pause = 0;
	else if (i == 3)
		d->pause = 1;
	else if (i == 4)
	{
		*running = 0;
		d->pause = 0;
	}
	else if (i == 5)
	{
		d->pause = 1;
		d->step = 1;
		*timeout = 0;
	}
}

void		event_button_bar(t_disp *d, int *timeout, int *running)
{
	int		i;

	i = 0;
	while (i < 6)
	{
		if (d->event.button.x >= 1980 + (90 * i)
				&& d->event.button.x <= 1980 + (90 * i) + 90
				&& d->event.button.y >= d->process.h - (d->process.h / 3) + 30
				&& d->event.button.y <= d->process.h - (d->process.h / 3) + 120)
		{
			event_button_bar2(d, i, timeout, running);
		}
		i++;
	}
	d->button_status = 1;
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
}

void		event_mousebutton(t_disp *d, int *running, int *timeout, t_arena a)
{
	int		i;
	int		j;
	int		ph;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	i = -1;
	while (i++ < a.nb_champs)
	{
		j = -1;
		while (j++ < 6)
		{
			if (d->event.button.x >= (d->players.x + d->players.w)
			- ((d->players.w / 6) * (j + 1)) + 20
			&& d->event.button.x <= (d->players.x + d->players.w)
			- ((d->players.w / 6) * (j + 1)) + 20 + 50
			&& d->event.button.y >= (d->players.y + (ph * i)) + (ph / 2) - 25
			&& d->event.button.y <= (d->players.y + (ph * i))
			+ (ph / 2) - 25 + 50)
			{
				event_button_players(d, i, j);
				event_button_players2(d, i, ph, a);
			}
		}
	}
	event_button_bar(d, timeout, running);
}
