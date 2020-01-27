/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:36:59 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/27 10:40:59 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		error(char *src, t_disp *d)
{
	printf("%s%s\n", src, SDL_GetError());
	SDL_DestroyTexture(d->back);
	SDL_DestroyRenderer(d->rend);
	SDL_DestroyWindow(d->win);
	TTF_CloseFont(d->font1);
	TTF_Quit();
	SDL_Quit();
	exit(1);
}

void		disp_ttf(char *ttf, SDL_Color color, t_disp *d)
{
	d->txt = TTF_RenderText_Blended(d->font1, ttf, color);
	d->font = SDL_CreateTextureFromSurface(d->rend, d->txt);
	if (SDL_RenderCopy(d->rend, d->font, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
}

void		disp_init(t_disp *d, t_arena a)
{
	int			i;
	int			ph;
	SDL_Color	color;
	char		nb_p[3];

	nb_p[2] = '\0';
	nb_p[0] = 'P';
	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champions);
	d->tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, d->screen.w, d->screen.h);
	d->a_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, d->screen.w, d->screen.h);
	d->b_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, d->arena.w, d->arena.h);
	d->p_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 300, 30);
	d->f_tmp = SDL_CreateTexture(d->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 540, (d->process.h / 3) - 20);
	color.a = 0;
	d->pause = 0;
	d->step = 0;
	d->delay = 1000;
	i = 1;
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->back, NULL, &d->screen) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 186, 186, 186, 100) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->arena) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_RenderFillRect(d->rend, &d->players) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_RenderFillRect(d->rend, &d->process) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->arena) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->players) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->process) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	while (i <= a.nb_champions)
	{
		if (!((d->font1 = TTF_OpenFont("img/font1.ttf", 65))))
			error("(menu.c) TTF_OpenFont : ", d);
		if (SDL_RenderDrawLine(d->rend, d->players.x, (ph * i) + d->players.y,
					(d->players.x + d->players.w), (ph * i) + d->players.y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, d->players.x, d->players.y + 70 + (ph * (i - 1)), d->players.x + 70, d->players.y + 70 + (ph * (i - 1))) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, d->players.x + 70, d->players.y + (ph * (i - 1)), d->players.x + 70, d->players.y + 70 + (ph * (i - 1))) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (i == 1)
			d->color_champ[i - 1] = 0xFF000000;
		else if (i == 2)
			d->color_champ[i - 1] = 0xFFFF0000;
		else if (i == 3)
			d->color_champ[i - 1] = 0x00FF0000;
		else if (i == 4)
			d->color_champ[i - 1] = 0x0000FF00;
		color.r = (d->color_champ[i - 1] & 0xFF000000) >> 24;
		color.g = (d->color_champ[i - 1] & 0xFF0000) >> 16;
		color.b = (d->color_champ[i - 1] & 0xFF00) >> 8;
		nb_p[1] = i + '0';
		d->mod.x = d->players.x + 5;
		d->mod.y = (ph * (i - 1)) + d->players.y + 5;
		d->mod.h = 70;
		d->mod.w = 60;
		disp_ttf(nb_p, color, d);
		i++;
	}
	TTF_CloseFont(d->font1);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 65))))
		error("(menu.c) TTF_OpenFont : ", d);
	d->mod.y = 20;
	d->mod.x = 1960;
	d->mod.w = 580;
	d->mod.h = 168;
	if (SDL_RenderCopy(d->rend, d->title, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	d->mod.x = 1980;
	d->mod.y = d->process.h + 20 - (d->process.h / 3);
	d->mod.w = 540;
	d->mod.h = (d->process.h / 3) - 20;
	if (SDL_SetRenderTarget(d->rend, d->f_tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 0) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->f_tmp, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 0) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->mod) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	d->process.x = 1960;
	d->process.y = 188;
	d->process.w = 580;
	d->process.h = 712;
	if (SDL_RenderDrawLine(d->rend, d->process.x + 1, d->process.y,
				d->process.x + d->process.w - 2, d->process.y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
	d->mod.x = d->process.x + 55 + (13 * 15);
	d->mod.h = 30;
	d->mod.w = 300;
	i = 0;
	while (i < 4)
	{
		if (SDL_SetRenderTarget(d->rend, d->p_tmp) < 0)
			error("(menu.c) SDL_SetRenderTarget : ", d);
		d->mod.y = d->process.y + 15 + (60 * i);
		if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 0) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		if (SDL_RenderFillRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);
		if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 0) < 0)
			error("(disp.c) SDL_SetRenderDrawColor : ", d);
		if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
			error("(menu.c) SDL_SetRenderTarget : ", d);
		if (SDL_RenderCopy(d->rend, d->p_tmp, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		if (SDL_RenderDrawRect(d->rend, &d->mod) < 0)
			error("(disp.c) SDL_RenderDrawRect : ", d);
		i++;
	}
	d->mod.x = d->process.x + 20;
	d->mod.h = 20;
	d->mod.w = 13 * 15;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	d->mod.y = d->process.y + 20;
	disp_ttf("Cycle_To_Die  :", color, d);
	d->mod.y = d->process.y + 80;
	disp_ttf("Cycle_Delta   :", color, d);
	d->mod.y = d->process.y + 140;
	disp_ttf("Nbr_Live      :", color, d);
	d->mod.y = d->process.y + 200;
	disp_ttf("Process       :", color, d);
	d->mod.x = 1980;
	d->mod.y = d->process.h - (d->process.h / 3) + 30;
	d->mod.w = 540;
	d->mod.h = 90;
	if (SDL_RenderCopy(d->rend, d->bar, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	////////////////////////////////////////////////////////////////////////
	d->arena.x += 1;
	d->arena.y += 1;
	d->arena.w -= 2;
	d->arena.h -= 2;
	if (SDL_SetRenderTarget(d->rend, d->b_tmp) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 186, 186, 186, 100) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderCopy(d->rend, d->back, &d->arena, NULL) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_RenderFillRect(d->rend, NULL) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(menu.c) SDL_SetRenderTarget : ", d);
	//////////////////////////////////////////////////////////////////////////
	SDL_RenderPresent(d->rend);
}

void			init_img_load(t_disp *d, SDL_Texture **tex, char *filename)
{
	if (!(d->img = IMG_Load(filename)))
		error("(main.c) IMG_Load : ", d);
	if (!(*tex = SDL_CreateTextureFromSurface(d->rend, d->img)))
		error("(main.c) SDL_CreateTextureFromSurface : ", d);
	SDL_FreeSurface(d->img);
}

void			init_img(t_disp *d)
{
	init_img_load(d, &d->back, "img/back2.jpg");
	init_img_load(d, &d->title, "img/core_title.xcf");
	init_img_load(d, &d->bar, "img/bar_button_press.xcf");
	init_img_load(d, &d->bar_plus, "img/button_plus_press.xcf");
	init_img_load(d, &d->bar_minus, "img/button_minus_press.xcf");
	init_img_load(d, &d->bar_play, "img/button_play_press.xcf");
	init_img_load(d, &d->bar_pause, "img/button_pause_press.xcf");
	init_img_load(d, &d->bar_stop, "img/button_stop_press.xcf");
	init_img_load(d, &d->bar_step, "img/button_step_press.xcf");
}

void		init_window(t_disp *d, t_arena a)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		error("(main.c) SDL_Init error : ", d);
	if (TTF_Init() == -1)
		error("(main.c) TTF_Init error : ", d);
	if (!(d->win = SDL_CreateWindow("COREWAR", 1000, 1000,
					0, 0, SDL_WINDOW_OPENGL)))
		error("(main.c) SDL_CreateWindow error : ", d);
	if (!(d->rend = SDL_CreateRenderer(d->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		error("(main.c) SDL_CreateRenderer error : ", d);
	if (SDL_SetWindowFullscreen(d->win, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
		error("(main.c) SDL_SetWindowFullscreen error : ", d);
	SDL_GetWindowSize(d->win, &d->screen.w, &d->screen.h);
	init_img(d);
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
	d->process.y = 20;
	d->process.w = 580;
	d->process.h = 880;
	disp_init(d, a);
}
