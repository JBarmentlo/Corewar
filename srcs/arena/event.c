/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:00:30 by ncoursol          #+#    #+#             */
/*   Updated: 2020/02/06 12:00:33 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

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
}
