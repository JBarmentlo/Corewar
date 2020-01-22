/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:32:17 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/22 14:39:40 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		events(t_disp *d, int *running, t_arena a)
{
	int			i;
	int			j;
	int			ph;

	if (d->event.type == SDL_QUIT || d->event.key.keysym.sym == SDLK_ESCAPE)
		*running = 0;
	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champions);
	i = 0;
	j = 0;
	if (d->event.type == SDL_MOUSEMOTION)
	{
		while (i < a.nb_champions)
		{
			if (d->event.motion.x >= d->players.x && d->event.motion.x <= d->players.x + d->players.w && d->event.motion.y >= d->players.y + (ph * i) && d->event.motion.y <= d->players.y + (ph * i) + ph)
			{
				d->mod = d->players;
				d->mod.y = d->players.y + (ph * i);
				d->mod.h = ph + 1;
				if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
					error("(menu.c) SDL_RenderCopy : ", d);
				if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
					error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
				if (SDL_SetRenderDrawColor(d->rend, 186, 186, 186, 150) < 0)
					error("(disp.c) SDL_SetRenderDrawColor : ", d);
				if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
					error("(disp.c) SDL_RenderFillRect : ", d);
				while (j < 6)
				{
					if (j == 0 && SDL_SetRenderDrawColor(d->rend, 255, 0, 0, 255) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 1 && SDL_SetRenderDrawColor(d->rend, 255, 255, 0, 255) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 2 &&SDL_SetRenderDrawColor(d->rend, 0, 255, 0, 255) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 3 && SDL_SetRenderDrawColor(d->rend, 0, 0, 255, 255) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 4 && SDL_SetRenderDrawColor(d->rend, 255, 0, 255, 255) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 5 && SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 255) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					d->mod.x = (d->players.x + d->players.w) - ((d->players.w / 6) * (j + 1)) + 20;
					d->mod.y = (d->players.y + (ph * i)) + (ph / 2) - 25;
					d->mod.w = 50;
					d->mod.h = 50;
					if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
						error("(disp.c) SDL_RenderFillRect : ", d);
					j++;
				}
				if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
					error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
				SDL_RenderPresent(d->rend);
				if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
					error("(menu.c) SDL_RenderCopy : ", d);
			}
			else if (d->mod.w == 50 && (d->event.motion.x < d->players.x || d->event.motion.x > d->players.x + d->players.w || d->event.motion.y < d->players.y || d->event.motion.y > d->players.y + d->players.h))
			{
				SDL_RenderPresent(d->rend);
				d->mod.w = 0;
			}
			i++;
		}
	}
	if (d->event.type == SDL_MOUSEBUTTONDOWN)
	{
		while (i < a.nb_champions)
		{
			if (d->event.button.x >= d->players.x && d->event.button.x <= d->players.x + d->players.w && d->event.button.y >= d->players.y + (ph * i) && d->event.button.y <= d->players.y + (ph * i) + ph)
			{

			}
			i++;
		}
	}
}
