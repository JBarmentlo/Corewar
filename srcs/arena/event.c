/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:00:30 by ncoursol          #+#    #+#             */
/*   Updated: 2020/02/20 14:15:13 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void        event_keydown(t_disp *d, int *running, int *timeout)
{
	if (d->event.key.type == SDL_KEYDOWN)
	{
		if (d->event.key.keysym.sym == SDLK_KP_PLUS
				|| d->event.key.keysym.sym == SDLK_PLUS)
			d->delay = (d->delay == 100 ? 100 : d->delay + 4);
		else if (d->event.key.keysym.sym == SDLK_KP_MINUS
				|| d->event.key.keysym.sym == SDLK_MINUS)
			d->delay = (d->delay == 1 ? 1 : d->delay - 4);
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
	if (d->event.type == SDL_QUIT || d->event.key.keysym.sym == SDLK_ESCAPE)
	{
		*running = 0;
		d->pause = 0;
	}
	if (d->event.type == SDL_MOUSEMOTION)
		event_mousemotion(d, timeout, a);
	if (d->event.type == SDL_MOUSEBUTTONDOWN && d->button_status != 1)
		event_mousebutton(d, running, timeout, a);
	if (d->event.type == SDL_KEYDOWN && d->button_status != 1)
		event_keydown(d, running, timeout);
}
