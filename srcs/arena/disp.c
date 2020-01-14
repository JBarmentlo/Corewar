/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:36:59 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/14 12:52:40 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		error(char *src, t_disp *d)
{
	printf("%s%s\n", src, SDL_GetError());
	SDL_DestroyTexture(d->back);
	SDL_DestroyRenderer(d->rend);
	SDL_DestroyWindow(d->win);
	SDL_Quit();
	exit(1);
}

void		disp_init(t_disp *d)
{
	if (SDL_SetRenderDrawColor(d->rend, 255, 0, 0, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->arena) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->players) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->process) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	SDL_RenderPresent(d->rend);
}

void		init_window(t_disp *d)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error("(main.c) SDL_Init error : ", d);
	if (!(d->win = SDL_CreateWindow("COREWAR", 1000, 1000,
					0, 0, SDL_WINDOW_OPENGL)))
		error("(main.c) SDL_CreateWindow error : ", d);
	if (!(d->rend = SDL_CreateRenderer(d->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error("(main.c) SDL_CreateRenderer error : ", d);
	if (SDL_SetWindowFullscreen(d->win, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		error("(main.c) SDL_SetWindowFullscreen error : ", d);
	SDL_GetWindowSize(d->win, &d->screen.w, &d->screen.h);
	if ((d->back = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
					SDL_TEXTUREACCESS_TARGET, d->screen.w, d->screen.h)) == NULL)
		error("(main.c) SDL_CreateTexture : ", d);
	d->screen.x = 0;
	d->screen.y = 0;

	d->arena.x = 20;
	d->arena.y = 20;
	d->arena.w = 1920;
	d->arena.h = 1400;
		d->players.x = 1960;
	d->players.y = 920;
	d->players.w = 580;
	d->players.h = 500;

	d->process.x = 1960;
	d->process.y = 400;
	d->process.w = 580;
	d->process.h = 500;
	disp_init(d);
}
