/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:36:59 by ncoursol          #+#    #+#             */
/*   Updated: 2020/01/15 16:11:01 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		error(char *src, t_disp *d)
{
	printf("%s%s\n", src, SDL_GetError());
	SDL_DestroyTexture(d->back);
	SDL_DestroyRenderer(d->rend);
	SDL_DestroyWindow(d->win);
	//TTF_CloseFont(d->font1);
	TTF_Quit();
	SDL_Quit();
	exit(1);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		disp_init(t_disp *d, t_arena a)
{
	int			i;
	int			ph;
	SDL_Color	color;
	char		nb_p[3];

	nb_p[2] = '\0';
	nb_p[0] = 'P';
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 0;
	ph = (((d->players.y + d->players.h) - d->players.y) / a.nb_champions);
	i = 1;
	if (SDL_RenderCopy(d->rend, d->back, NULL, &d->screen) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(menu.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 186, 186, 186, 100) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->arena) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderFillRect(d->rend, &d->players) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderFillRect(d->rend, &d->process) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
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
		if (!((d->font1 = TTF_OpenFont("img/font1.ttf", (ph / 2) - 2))))
			error("(menu.c) TTF_OpenFont : ", d);
		if (SDL_RenderDrawLine(d->rend, d->players.x, (ph * i) + d->players.y,
		(d->players.x + d->players.w), (ph * i) + d->players.y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, d->players.x,
		((ph * i) - (ph / 2)) + d->players.y, d->players.x + (ph / 2),
		((ph * i) - (ph / 2)) + d->players.y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (SDL_RenderDrawLine(d->rend, d->players.x + (ph / 2),
		(ph * (i - 1)) + d->players.y, d->players.x + (ph / 2),
		((ph * i) - (ph / 2)) + d->players.y) < 0)
			error("(disp.c) SDL_RenderDrawLine : ", d);
		if (i == 1)
			color.r = 255;
		else if (i == 2)
			color.g = 255;
		else if (i == 3)
			color.r = 0;
		else if (i == 4)
		{
			color.g = 0;
			color.b = 255;
		}
		nb_p[1] = i + '0';
		d->txt = TTF_RenderText_Blended(d->font1, nb_p, color);
		d->font = SDL_CreateTextureFromSurface(d->rend, d->txt);
		d->mod.x = d->players.x + 5;
		d->mod.y = (ph * (i - 1)) + d->players.y + 5;
		d->mod.h = (ph / 2);
		d->mod.w = (ph / 2) - 10;
		if (SDL_RenderCopy(d->rend, d->font, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		if (ft_strlen(a.champion_table[i - 1].name) >= 16 && ft_strlen(a.champion_table[i - 1].name) > 19)
		{
			a.champion_table[i - 1].name[16] = '.';
			a.champion_table[i - 1].name[17] = '.';
			a.champion_table[i - 1].name[18] = '.';
			a.champion_table[i - 1].name[19] = '\0';
		}
		if (!((d->font1 = TTF_OpenFont("img/font2.ttf", ((d->players.w - 10) - (ph / 2) + 10) / 20 + 10))))
			error("(menu.c) TTF_OpenFont : ", d);
		d->txt = TTF_RenderText_Blended(d->font1, "Name :", color);
		d->font = SDL_CreateTextureFromSurface(d->rend, d->txt);
		d->mod.x = d->players.x + (ph / 2) + 10;
		d->mod.y = (ph * (i - 1)) + d->players.y + 5;
		d->mod.h = ((d->players.w - 10) - (ph / 2) + 10) / 20;
		d->mod.w = ((d->players.w - 10) - (ph / 2) + 10) / 7 + 7;
		if (SDL_RenderCopy(d->rend, d->font, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		d->txt = TTF_RenderText_Blended(d->font1, a.champion_table[i - 1].name, color);
		d->font = SDL_CreateTextureFromSurface(d->rend, d->txt);
		d->mod.y = (ph * (i - 1)) + d->players.y + 5;
		d->mod.x = d->players.x + (ph / 2) + 20 + (((d->players.w - 10) - (ph / 2) + 10) / 7 + 7);
		d->mod.w = ft_strlen(a.champion_table[i - 1].name) * (((d->players.w - 10) - (ph / 2) + 10) / 20 - 5);
		if (SDL_RenderCopy(d->rend, d->font, NULL, &d->mod) < 0)
			error("(menu.c) SDL_RenderCopy : ", d);
		i++;
	}
	d->mod.y = 20;
	d->mod.x = 1960;
	d->mod.w = 580;
	d->mod.h = 168;
	if (SDL_RenderCopy(d->rend, d->title, NULL, &d->mod) < 0)
		error("(menu.c) SDL_RenderCopy : ", d);
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
