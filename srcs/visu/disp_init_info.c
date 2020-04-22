/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_init_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 16:08:57 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 12:45:13 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void			disp_init_info2(t_disp *d)
{
	d->mod.y = 20;
	d->mod.x = 1960;
	d->mod.w = 580;
	d->mod.h = 168;
	if (SDL_RenderCopy(d->rend, d->title, NULL, &d->mod) < 0)
		error("(disp_init_info.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 50, 50, 50, 0) < 0)
		error("(disp_init_info.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_SetRenderTarget(d->rend, d->f_tmp) < 0)
		error("(disp_init_info.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderFillRect(d->rend, NULL) < 0)
		error("(disp_init_info.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 0) < 0)
		error("(disp_init_info.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, NULL) < 0)
		error("(disp_init_info.c) SDL_RenderDrawRect : ", d);
	if (SDL_RenderDrawLine(d->rend, 0, 20, d->mod.w, 20) < 0)
		error("(disp_init_info.c) SDL_RenderDrawLine : ", d);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 17))))
		error("(disp_init_info.c) TTF_OpenFont : ", d);
	d->mod.x = 15;
	d->mod.y = 0;
	disp_ttf("Name", d->color, d);
	d->mod.x = 245;
	disp_ttf("Op", d->color, d);
}

void			disp_init_info3(t_disp *d)
{
	d->mod.x = 345;
	disp_ttf("Cycles", d->color, d);
	d->mod.x = 445;
	disp_ttf("PC", d->color, d);
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(disp_init_info.c) SDL_SetRenderTarget : ", d);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 25))))
		error("(disp_init_info.c) TTF_OpenFont : ", d);
	d->process.x = 1960;
	d->process.y = 188;
	d->process.w = 580;
	d->process.h = 712;
	if (SDL_RenderDrawLine(d->rend, d->process.x + 1, d->process.y,
				d->process.x + d->process.w - 2, d->process.y) < 0)
		error("(disp_init_info.c) SDL_RenderDrawLine : ", d);
	d->mod.x = d->process.x + 55 + (13 * 15);
	d->mod.h = 30;
	d->mod.w = 300;
}

void			disp_init_info4(t_disp *d, int i)
{
	if (SDL_SetRenderTarget(d->rend, d->p_tmp) < 0)
		error("(disp_init_info.c) SDL_SetRenderTarget : ", d);
	d->mod.y = d->process.y + 15 + (60 * i);
	if (SDL_SetRenderDrawColor(d->rend, 0, 0, 0, 0) < 0)
		error("(disp_init_info.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderFillRect(d->rend, NULL) < 0)
		error("(disp_init_info.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderDrawColor(d->rend, 255, 255, 255, 0) < 0)
		error("(disp_init_info.c) SDL_SetRenderDrawColor : ", d);
	if (SDL_RenderDrawRect(d->rend, NULL) < 0)
		error("(disp_init_info.c) SDL_RenderDrawRect : ", d);
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(disp_init_info.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->p_tmp, NULL, &d->mod) < 0)
		error("(disp_init_info.c) SDL_RenderCopy : ", d);
}

void			disp_init_info5(t_disp *d)
{
	d->mod.x = d->process.x + 20;
	d->mod.h = 20;
	d->mod.w = 13 * 15;
	d->mod.y = d->process.y + 20;
	disp_ttf("Cycle_To_Die  :", d->color, d);
	d->mod.y = d->process.y + 80;
	disp_ttf("Cycle_Delta   :", d->color, d);
	d->mod.y = d->process.y + 140;
	disp_ttf("Nbr_Live      :", d->color, d);
	d->mod.y = d->process.y + 200;
	disp_ttf("Process       :", d->color, d);
	d->mod.y = d->process.y + 260;
	disp_ttf("Cycles        :", d->color, d);
	d->mod.x = 1980;
	d->mod.y = d->process.h - (d->process.h / 3) + 30;
	d->mod.w = 540;
	d->mod.h = 90;
}

void			disp_init_info(t_disp *d)
{
	int		i;

	disp_init_info2(d);
	disp_init_info3(d);
	i = 0;
	while (i < 5)
	{
		disp_init_info4(d, i);
		i++;
	}
	disp_init_info5(d);
	if (SDL_RenderCopy(d->rend, d->bar, NULL, &d->mod) < 0)
		error("(disp_init_info.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_init_info.c) SDL_SetRenderTarget : ", d);
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(disp_init_info.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(disp_init_info.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(disp_init_info.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(disp_init_info.c) SDL_RenderCopy : ", d);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
}
