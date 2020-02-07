/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_corewar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:32:17 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/27 12:42:03 by dberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		events(t_disp *d, int *running, int *timeout, t_arena a)
{
	int			i;
	int			j;
	int			ph;
	char		p[3];
	SDL_Color	color;

	if (d->event.type == SDL_QUIT || d->event.key.keysym.sym == SDLK_ESCAPE)
		*running = 0;
	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champs);
	i = 0;
	if (d->event.type == SDL_MOUSEMOTION)
	{
		while (i < a.nb_champs)
		{
			if (d->event.motion.x >= d->players.x
					&& d->event.motion.x <= d->players.x + d->players.w
					&& d->event.motion.y >= d->players.y + (ph * i)
					&& d->event.motion.y <= d->players.y + (ph * i) + ph)
			{
				j = 0;
				d->mod = d->players;
				d->mod.y = d->players.y + (ph * i);
				d->mod.h = ph + 1;
				if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
					error("(menu.c) SDL_SetRenderTarget : ", d);
				if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
					error("(menu.c) SDL_RenderCopy : ", d);
				if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
					error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
				if (SDL_SetRenderDrawColor(d->rend, 186, 186, 186, 255) < 0)
					error("(disp.c) SDL_SetRenderDrawColor : ", d);
				if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
					error("(disp.c) SDL_RenderFillRect : ", d);
				while (j < 6)
				{
					if (j == 0 && SDL_SetRenderDrawColor(d->rend, 255, 0, 0, 155) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 1 && SDL_SetRenderDrawColor(d->rend, 255, 255, 0, 155) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 2 &&SDL_SetRenderDrawColor(d->rend, 0, 255, 0, 155) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 3 && SDL_SetRenderDrawColor(d->rend, 0, 0, 255, 155) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 4 && SDL_SetRenderDrawColor(d->rend, 255, 0, 255, 155) < 0)
						error("(disp.c) SDL_SetRenderDrawColor : ", d);
					if (j == 5 && SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 155) < 0)
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
				if (SDL_SetRenderTarget(d->rend, NULL) < 0)
					error("(menu.c) SDL_SetRenderTarget : ", d);
				if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
					error("(menu.c) SDL_RenderCopy : ", d);
				SDL_RenderPresent(d->rend);
			}
			else if (d->mod.w == 50 && (d->event.motion.x < d->players.x
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
		while (i < 6)
		{
			if (d->event.motion.x >= 1980 + (90 * i)
					&& d->event.motion.x <= 1980 + (90 * i) + 90
					&& d->event.motion.y >= d->process.h - (d->process.h / 3) + 30
					&& d->event.motion.y <= d->process.h - (d->process.h / 3) + 120)
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
			i++;
		}
	}

	if (d->event.type == SDL_MOUSEBUTTONDOWN)
	{
		i = 0;
		while (i < a.nb_champs)
		{
			j = 0;
			while (j < 6)
			{
				if (d->event.button.x >= (d->players.x + d->players.w) - ((d->players.w / 6) * (j + 1)) + 20
						&& d->event.button.x <= (d->players.x + d->players.w) - ((d->players.w / 6) * (j + 1)) + 20 + 50
						&& d->event.button.y >= (d->players.y + (ph * i)) + (ph / 2) - 25
						&& d->event.button.y <= (d->players.y + (ph * i)) + (ph / 2) - 25 + 50)
				{
					if (j == 0)
						d->color_champ[i] = 0xFF000000;
					else if (j == 1)
						d->color_champ[i] = 0xFFFF0000;
					else if (j == 2)
						d->color_champ[i] = 0x00FF0000;
					else if (j == 3)
						d->color_champ[i] = 0x0000FF00;
					else if (j == 4)
						d->color_champ[i] = 0xFF00FF00;
					else if (j == 5)
						d->color_champ[i] = 0x00000000;
					if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
						error("(menu.c) SDL_SetRenderTarget : ", d);
					TTF_CloseFont(d->font1);
					if (!((d->font1 = TTF_OpenFont("img/font1.ttf", 65))))
						error("(menu.c) TTF_OpenFont : ", d);
					p[0] = 'P';
					p[1] = (i + 1) + '0';
					p[2] = '\0';
					color.a = 0;
					color.r = (d->color_champ[i] & 0xFF000000) >> 24;
					color.g = (d->color_champ[i] & 0xFF0000) >> 16;
					color.b = (d->color_champ[i] & 0xFF00) >> 8;
					d->mod.x = d->players.x + 5;
					d->mod.y = (ph * i) + d->players.y + 5;
					d->mod.h = 70;
					d->mod.w = 60;
					disp_ttf(p, color, d);
					if (SDL_SetRenderTarget(d->rend, NULL) < 0)
						error("(menu.c) SDL_SetRenderTarget : ", d);
				}
				j++;
			}
			i++;
		}
		i = 0;
		while (i < 6)
		{
			if (d->event.button.x >= 1980 + (90 * i)
					&& d->event.button.x <= 1980 + (90 * i) + 90
					&& d->event.button.y >= d->process.h - (d->process.h / 3) + 30
					&& d->event.button.y <= d->process.h - (d->process.h / 3) + 120)
			{
				if (i == 0)
				{
					d->delay -= 50;
					*timeout -= 50;
				}
				else if (i == 1)
				{
					d->delay += 50;
					*timeout += 50;
				}
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
				}
			}
			i++;
		}

	}
}
