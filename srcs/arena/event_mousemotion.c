/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mousemotion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 17:52:35 by ncoursol          #+#    #+#             */
/*   Updated: 2020/02/13 12:13:48 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void			event_motion_bar2(t_disp *d, int i)
{
	d->mod.x = 1980 + (90 * i) + 2;
	d->mod.y = d->process.h - (d->process.h / 3) + 33;
	d->mod.h = 83;
	d->mod.w = 88;
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (i == 0 && SDL_RenderCopy(d->rend, d->bar_plus, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	else if (i == 1 && SDL_RenderCopy(d->rend, d->bar_minus, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	else if (i == 2 && SDL_RenderCopy(d->rend, d->bar_play, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	else if (i == 3 && SDL_RenderCopy(d->rend, d->bar_pause, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	else if (i == 4 && SDL_RenderCopy(d->rend, d->bar_stop, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	else if (i == 5 && SDL_RenderCopy(d->rend, d->bar_step, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
}

void			event_motion_bar(t_disp *d, int i)
{
	if (d->event.motion.x >= 1980 + (90 * i)
			&& d->event.motion.x <= 1980 + (90 * i) + 90
			&& d->event.motion.y >= d->process.h - (d->process.h / 3) + 30
			&& d->event.motion.y <= d->process.h - (d->process.h / 3) + 120)
	{
		event_motion_bar2(d, i);
	}
	else if (d->mod.w == 90 && (d->event.motion.x < 1980
				|| d->event.motion.x > 1980 + 540
				|| d->event.motion.y < d->process.h - (d->process.h / 3) + 30
				|| d->event.motion.y > d->process.h - (d->process.h / 3) + 120))
	{
		if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
			error("(menu.c) SDL_SetRenderTarget : ", d);
		if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(menu.c) SDL_SetRenderTarget : ", d);
		if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
		d->mod.w = 0;
	}
}

void			event_motion_players2(t_disp *d, int *timeout, int i, int ph)
{
	int		j;

	j = 0;
	while (j < 6 && (!SDL_TICKS_PASSED(SDL_GetTicks(), *timeout) || d->pause == 1))
	{
		if (j == 0 && SDL_SetRenderDrawColor(d->rend, 255, 0, 0, 155) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		else if (j == 1 && SDL_SetRenderDrawColor(d->rend, 255, 255, 0, 155) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		else if (j == 2 && SDL_SetRenderDrawColor(d->rend, 0, 255, 0, 155) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		else if (j == 3 && SDL_SetRenderDrawColor(d->rend, 0, 0, 255, 155) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		else if (j == 4 && SDL_SetRenderDrawColor(d->rend, 255, 0, 255, 155) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		else if (j == 5 && SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 155) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		d->mod.x = (d->players.x + d->players.w) - ((d->players.w / 6) * (j + 1)) + 20;
		d->mod.y = (d->players.y + (ph * i)) + (ph / 2) - 25;
		d->mod.w = 50;
		d->mod.h = 50;
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderFillRect : ", d);
		j++;
	}
}

void			event_motion_players(t_disp *d, int *timeout, int i, int ph)
{
	if (d->pause == 1 && d->event.motion.x >= d->players.x
			&& d->event.motion.x <= d->players.x + d->players.w
			&& d->event.motion.y >= d->players.y + (ph * i)
			&& d->event.motion.y <= d->players.y + (ph * i) + ph)
	{
		d->mod = d->players;
		d->mod.y = d->players.y + (ph * i) + 1;
		d->mod.h = ph - 1;
		d->mod.x += 1;
		d->mod.w -= 2;
		if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
			error("(menu.c) SDL_SetRenderTarget : ", d);
		if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		if (SDL_SetRenderDrawColor(d->rend, 50, 50, 50, 255) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderFillRect : ", d);
		event_motion_players2(d, timeout, i, ph);
		if (SDL_SetRenderTarget(d->rend, NULL) < 0)
			error("(menu.c) SDL_SetRenderTarget : ", d);
		if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		SDL_RenderPresent(d->rend);
	}
}

void		event_mousemotion(t_disp *d, int *timeout, t_arena a)
{
	int		i;
	int         ph;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	i = 0;
	while (i < a.nb_champs && (!SDL_TICKS_PASSED(SDL_GetTicks(), *timeout) || d->pause == 1))
	{
		event_motion_players(d, timeout, i, ph);
		if (d->mod.w == 50 && (d->event.motion.x < d->players.x
					|| d->event.motion.x > d->players.x + d->players.w
					|| d->event.motion.y < d->players.y
					|| d->event.motion.y > d->players.y + d->players.h))
		{
			if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
				error("(menu.c) SDL_SetRenderTarget : ", d);
			if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
				error("(menu.c) SDL_RenderCopy : ", d);
			if (SDL_SetRenderTarget(d->rend, NULL) < 0)
				error("(menu.c) SDL_SetRenderTarget : ", d);
			if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
				error("(menu.c) SDL_RenderCopy : ", d);
			SDL_RenderPresent(d->rend);
			d->mod.w = 0;
		}
		i++;
	}
	i = 0;
	while (i < 6 && (!SDL_TICKS_PASSED(SDL_GetTicks(), *timeout) || d->pause == 1))
	{
		event_motion_bar(d, i);
		i++;
	}
}
