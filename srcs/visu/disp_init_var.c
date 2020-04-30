/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_init_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:25:33 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:17:31 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		error2(t_disp *d)
{
	SDL_DestroyTexture(d->back);
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
	SDL_DestroyWindow(d->win);
	SDL_DestroyRenderer(d->rend);
	TTF_Quit();
	SDL_Quit();
	exit(1);
}

void		error(char *src, t_disp *d)
{
	if (ft_strcmp(src, "TTF"))
		ft_printf("%s%s\n", src, TTF_GetError());
	else if (ft_strcmp(src, "SDL"))
		ft_printf("%s%s\n", src, SDL_GetError());
	else if (ft_strcmp(src, "IMG"))
		ft_printf("%s%s\n", src, IMG_GetError());
	else
		ft_printf("%s\n", src);
	if (d->img != NULL)
		SDL_FreeSurface(d->img);
	if (d->txt != NULL)
		SDL_FreeSurface(d->txt);
	if (d->s_arena != NULL)
		SDL_FreeSurface(d->s_arena);
	if (d->font1 != NULL)
		TTF_CloseFont(d->font1);
	error2(d);
}

void		disp_ttf(char *ttf, SDL_Color color, t_disp *d)
{
	if (ttf[0] != '\0')
	{
		if ((d->txt = TTF_RenderText_Blended(d->font1, ttf, color)) == NULL)
			error("(disp_init_var.c) TTF_RenderText_Blended : ", d);
		if ((d->font = SDL_CreateTextureFromSurface(d->rend, d->txt)) == NULL)
			error("(disp_init_var.c) SDL_CreateTextureFromSurface : ", d);
		SDL_FreeSurface(d->txt);
		d->txt = NULL;
		if (SDL_QueryTexture(d->font, NULL, NULL, &d->mod.w, &d->mod.h) < 0)
			error("(disp_init_var.c) SDL_QueryTexture : ", d);
		if (SDL_RenderCopy(d->rend, d->font, NULL, &d->mod) < 0)
			error("(disp_init_var.c) SDL_RenderCopy : ", d);
		SDL_DestroyTexture(d->font);
		d->font = NULL;
	}
}

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
	if (!d->tmp || !d->a_tmp || !d->b_tmp || !d->p_tmp || !d->f_tmp)
		error("(disp_init_var.c) SDL_CreateTexture : ", d);
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
		error("(disp_init_var.c) SDL_Init error : ", d);
	if (TTF_Init() == -1)
		error("(disp_init_var.c) TTF_Init error : ", d);
	if (!(d->win = SDL_CreateWindow("Visu Corewar", 1000, 1000,
					0, 0, SDL_WINDOW_OPENGL)))
		error("(disp_init_var.c) SDL_CreateWindow error : ", d);
	if (!(d->rend = SDL_CreateRenderer(d->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error("(disp_init_var.c) SDL_CreateRenderer error : ", d);
	if (SDL_SetWindowFullscreen(d->win, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		error("(disp_init_var.c) SDL_SetWindowFullscreen error : ", d);
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
