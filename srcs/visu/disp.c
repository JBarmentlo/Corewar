/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 12:36:59 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 14:47:01 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		disp_init_main(t_disp *d)
{
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(disp.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->back, NULL, &d->screen) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 186, 186, 186, 100) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, &d->arena) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_RenderFillRect(d->rend, &d->players) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_RenderFillRect(d->rend, &d->process) < 0)
		error("(disp.c) SDL_RenderFillRect : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 250) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->arena) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->players) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderDrawRect(d->rend, &d->process) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
}

void		disp_init_layer(t_disp *d)
{
	d->arena.x += 1;
	d->arena.y += 1;
	d->arena.w -= 2;
	d->arena.h -= 2;
	if (SDL_SetRenderTarget(d->rend, d->b_tmp) < 0)
		error("(disp.c) SDL_SetRenderTarget : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_BLEND) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 186, 186, 186, 100) < 0)
		error("(disp.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderCopy(d->rend, d->back, &d->arena, NULL) < 0)
		error("(disp.c) SDL_RenderCopy : ", d);
	if (SDL_RenderFillRect(d->rend, NULL) < 0)
		error("(disp.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawBlendMode(d->rend, SDL_BLENDMODE_NONE) < 0)
		error("(disp.c) SDL_SetRenderDrawBlendMode error : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp.c) SDL_SetRenderTarget : ", d);
}

void		init_img_load(t_disp *d, SDL_Texture **tex, char *filename)
{
	if (!(d->img = IMG_Load(filename)))
		error("(disp.c) IMG_Load : ", d);
	if (!(*tex = SDL_CreateTextureFromSurface(d->rend, d->img)))
		error("(disp.c) SDL_CreateTextureFromSurface : ", d);
	SDL_FreeSurface(d->img);
	d->img = NULL;
}

void		disp_init_img(t_disp *d)
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
	(void)a;
	disp_init_var(d);
	disp_init_img(d);
	disp_init_main(d);
	disp_init_players(d, a);
	disp_init_info(d);
	disp_init_layer(d);
	SDL_RenderPresent(d->rend);
}
