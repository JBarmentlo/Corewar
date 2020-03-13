/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info_global.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:56:10 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 17:19:10 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		update_info_global2(t_disp *d, t_arena a, char **info, int i)
{
	if (i == 0)
		*info = ft_itoa(a.cycle_to_die);
	else if (i == 1)
		*info = ft_itoa(CYCLE_DELTA);
	else if (i == 2)
		*info = ft_itoa(a.total_live_since_check);
	else if (i == 3)
		*info = ft_itoa(a.total_process_nb);
	else if (i == 4)
	{
		*info = ft_itoa(a.cycle % a.cycle_to_die);
		disp_ttf(*info, d->color, d);
		d->mod.x += ft_strlen(*info) * 18;
		free(*info);
		disp_ttf(" (", d->color, d);
		d->mod.x += 15;
		*info = ft_itoa(d->delay * 10);
		disp_ttf(*info, d->color, d);
		d->mod.x += ft_strlen(*info) * 20;
		free(*info);
		disp_ttf(".cps)", d->color, d);
	}
}

void		update_info_global(t_disp *d, t_arena a, char *info, int i)
{
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 30))))
		error("(update_visu.c) TTF_OpenFont : ", d);
	d->color.r = 255;
	d->color.g = 255;
	d->color.b = 255;
	d->mod.h = 30;
	while (i < 5)
	{
		d->mod.y = d->process.y + 15 + (60 * i);
		d->mod.x = d->process.x + 55 + (13 * 15);
		d->mod.w = 300;
		if (SDL_RenderCopy(d->rend, d->p_tmp, NULL, &d->mod) < 0)
			error("(update_visu.c) SDL_RenderCopy : ", d);
		d->mod.x += 5;
		update_info_global2(d, a, &info, i);
		if (i < 4)
		{
			disp_ttf(info, d->color, d);
			free(info);
		}
		i++;
	}
}
