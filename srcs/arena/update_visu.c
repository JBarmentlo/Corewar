/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:34:21 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:35:19 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		update_visu2(t_disp *d)
{
	if (SDL_SetRenderTarget(d->rend, d->a_tmp) < 0)
		error("(update_visu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->tmp, NULL, NULL) < 0)
		error("(update_visu.c) SDL_RenderCopy : ", d);
	if (SDL_SetRenderTarget(d->rend, NULL) < 0)
		error("(update_visu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->a_tmp, NULL, NULL) < 0)
		error("(update_visu.c) SDL_RenderCopy : ", d);
}

void		update_visu(t_disp *d, t_arena a)
{
	int			i;
	char		*info;

	i = 0;
	info = NULL;
	if (SDL_SetRenderTarget(d->rend, d->tmp) < 0)
		error("(update_visu.c) SDL_SetRenderTarget : ", d);
	if (SDL_RenderCopy(d->rend, d->b_tmp, NULL, &d->arena) < 0)
		error("(update_visu.c) SDL_RenderCopy : ", d);
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 19))))
		error("(update_visu.c) TTF_OpenFont : ", d);
	update_arena(d, a, i);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
	update_info_global(d, a, info, i);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
	update_info_players(d, a, info, i);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
	update_info_op(d, a, info, i);
	TTF_CloseFont(d->font1);
	d->font1 = NULL;
	update_visu2(d);
	SDL_RenderPresent(d->rend);
}
