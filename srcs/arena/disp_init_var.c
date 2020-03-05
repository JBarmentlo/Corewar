/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_init_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:25:33 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/02 20:01:32 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

/*
** usefull functions
*/

void        error(char *src, t_disp *d)
{
	if (ft_strcmp(src, "TTF"))
		printf("%s%s\n", src, TTF_GetError());
	else if (ft_strcmp(src, "SDL"))
		printf("%s%s\n", src, SDL_GetError());
	else
		printf("%s\n", src);
    SDL_DestroyTexture(d->back);
    SDL_DestroyRenderer(d->rend);

///////////////////////////////////////////////////////

    SDL_DestroyTexture(d->title);
    SDL_DestroyTexture(d->bar);
    SDL_DestroyTexture(d->bar_plus);
    SDL_DestroyTexture(d->bar_minus);
    SDL_DestroyTexture(d->bar_pause);
    SDL_DestroyTexture(d->bar_stop);
    SDL_DestroyTexture(d->bar_step);
    SDL_DestroyTexture(d->bar_play);
    SDL_DestroyTexture(d->font);
    SDL_DestroyTexture(d->tmp);
    SDL_DestroyTexture(d->a_tmp);
    SDL_DestroyTexture(d->b_tmp);
    SDL_DestroyTexture(d->p_tmp);
    SDL_DestroyTexture(d->f_tmp);





///////////////////////////////////////////////////////

    SDL_DestroyWindow(d->win);
    TTF_CloseFont(d->font1);
    TTF_Quit();
    SDL_Quit();
    exit(1);
}

void        disp_ttf(char *ttf, SDL_Color color, t_disp *d)
{
    d->txt = TTF_RenderText_Solid(d->font1, ttf, color);
    d->font = SDL_CreateTextureFromSurface(d->rend, d->txt);
	SDL_FreeSurface(d->txt);
	SDL_QueryTexture(d->font, NULL, NULL, &d->mod.w, &d->mod.h);
    if (SDL_RenderCopy(d->rend, d->font, NULL, &d->mod) < 0)
        error("(menuc) SDL_RenderCopy : ", d);
	SDL_DestroyTexture(d->font);
}

/*
** init var functions
*/

void		disp_init_var2(t_disp *d)
{
    d->process.x = 1960;
    d->process.y = 20;
    d->process.w = 580;
    d->process.h = 880;
	d->tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, d->screen.w, d->screen.h);
	d->a_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, d->screen.w, d->screen.h);
	d->b_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, d->arena.w, d->arena.h);
	d->p_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, 300, 30);
	d->f_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, 540, (d->process.h / 3) - 20);
	d->color_champ[0] = 0x8A8A8A00;
	d->pause = 0;
    d->step = 0;
	d->color.a = 0;
    d->delay = 10;
	d->d_cycle = 100;
}

void		disp_init_var(t_disp *d)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
        error("(main.c) SDL_Init error : ", d);
    if (TTF_Init() == -1)
        error("(main.c) TTF_Init error : ", d);
    if (!(d->win = SDL_CreateWindow("Visu Corewar", 1000, 1000,
                    0, 0, SDL_WINDOW_OPENGL)))
        error("(main.c) SDL_CreateWindow error : ", d);
    if (!(d->rend = SDL_CreateRenderer(d->win, -1,
                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
        error("(main.c) SDL_CreateRenderer error : ", d);
    if (SDL_SetWindowFullscreen(d->win, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
        error("(main.c) SDL_SetWindowFullscreen error : ", d);
    SDL_GetWindowSize(d->win, &d->screen.w, &d->screen.h);
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
	disp_init_var2(d);
}
