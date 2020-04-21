/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:00:30 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:39:13 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		event_motion_bar3(t_disp *d, int i)
{
	d->mod.x = 1980 + (90 * i) + 2;
	d->mod.y = d->process.h - (d->process.h / 3) + 33;
	d->mod.h = 83;
	d->mod.w = 88;
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(event_mousemotion.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	if (i == 0 && SDL_RenderCopy(d->rend, d->bar_plus, NULL, &d->mod) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	else if (i == 1 && SDL_RenderCopy(d->rend, d->bar_minus, NULL, &d->mod) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	else if (i == 2 && SDL_RenderCopy(d->rend, d->bar_play, NULL, &d->mod) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	else if (i == 3 && SDL_RenderCopy(d->rend, d->bar_pause, NULL, &d->mod) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	else if (i == 4 && SDL_RenderCopy(d->rend, d->bar_stop, NULL, &d->mod) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	else if (i == 5 && SDL_RenderCopy(d->rend, d->bar_step, NULL, &d->mod) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(event_mousemotion.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
		error("(event_mousemotion.c) SDL_RenderCopy : ", d);
	SDL_RenderPresent(d->rend);
}

void		event_button_players3(t_disp *d, int i, t_arena a)
{
	if (SDL_SetRenderDrawColor(d->rend, 50, 50, 50, 250) < 0)
		error("(event_mousebutton.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(event_mousebutton.c) SDL_RenderDrawRect : ", d);
	d->mod.w = ((d->players.w - 12) * a.champion_table[i].total_process)
		/ a.total_process_nb;
	if (SDL_SetRenderDrawColor(d->rend,
	(d->color_champ[i + 1] & 0xFF000000) >> 24,
	(d->color_champ[i + 1] & 0xFF0000) >> 16,
	(d->color_champ[i + 1] & 0xFF00) >> 8, 150) < 0)
		error("(event_mousebutton.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(event_mousebutton.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(event_mousebutton.c) SDL_SetRenderTarget : ", d);
}

void		event_keydown(t_disp *d, int *running, int *timeout)
{
	if (d->event.key.type == SDL_KEYDOWN)
	{
		if (d->event.key.keysym.sym == SDLK_KP_PLUS
				|| d->event.key.keysym.sym == SDLK_PLUS)
			d->delay = (d->delay >= 100 ? 100 : d->delay + 4);
		else if (d->event.key.keysym.sym == SDLK_KP_MINUS
				|| d->event.key.keysym.sym == SDLK_MINUS)
			d->delay = (d->delay <= 10 ? 10 : d->delay - 4);
		else if (d->pause == 1 && d->event.key.keysym.sym == SDLK_SPACE)
			d->pause = 0;
		else if (d->pause == 0 && d->event.key.keysym.sym == SDLK_SPACE)
			d->pause = 1;
		else if (d->event.key.keysym.sym == SDLK_ESCAPE)
		{
			*running = 0;
			d->pause = 0;
		}
		else if (d->event.key.keysym.sym == SDLK_RETURN
				|| d->event.key.keysym.sym == SDLK_RETURN2)
		{
			d->pause = 1;
			d->step = 1;
			*timeout = 0;
		}
	}
}

void		events(t_disp *d, int *running, int *timeout, t_arena a)
{
	int		ph;

	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	if (d->event.type == SDL_QUIT || d->event.key.keysym.sym == SDLK_ESCAPE)
	{
		*running = 0;
		d->pause = 0;
	}
	if (d->event.type == SDL_MOUSEMOTION)
		event_mousemotion(d, timeout, a, ph);
	if (d->event.type == SDL_MOUSEBUTTONDOWN && d->button_status != 1)
		event_mousebutton(d, running, timeout, a);
	if (d->event.type == SDL_KEYDOWN && d->button_status != 1)
		event_keydown(d, running, timeout);
}
