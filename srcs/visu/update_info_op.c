/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:46:29 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/12 16:53:29 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

void		update_info_op3(t_disp *d, t_arena a, char *info)
{
	disp_ttf(a.process_list->owner->header.prog_name, d->color, d);
	d->mod.x = 2225;
	disp_ttf(a.process_list->current_op->name, d->color, d);
	d->mod.x = 2325;
	info = ft_itoa(a.process_list->current_op->cycle_to_wait);
	disp_ttf(info, d->color, d);
	free(info);
	d->mod.x = 2425;
	info = ft_itoa(a.process_list->pc);
	disp_ttf(info, d->color, d);
	free(info);
	d->mod.y += 15;
}

void		update_info_op2(t_disp *d, t_arena a, char *info, int i)
{
	while (a.process_list && i < 16)
	{
		if (a.process_list->current_op)
		{
			d->color.r = (d->color_champ[a.process_list->owner->number]
					& 0xFF000000) >> 24;
			d->color.g = (d->color_champ[a.process_list->owner->number]
					& 0xFF0000) >> 16;
			d->color.b = (d->color_champ[a.process_list->owner->number]
					& 0xFF00) >> 8;
			d->mod.x = 1995;
			if (ft_strlen(a.process_list->owner->header.prog_name) > 18)
			{
				a.process_list->owner->header.prog_name[15] = '.';
				a.process_list->owner->header.prog_name[16] = '.';
				a.process_list->owner->header.prog_name[17] = '.';
				a.process_list->owner->header.prog_name[18] = '\0';
			}
			update_info_op3(d, a, info);
			i++;
		}
		a.process_list = a.process_list->next_list;
	}
}

void		update_info_op(t_disp *d, t_arena a, char *info, int i)
{
	if (!((d->font1 = TTF_OpenFont("img/font2.ttf", 18))))
		error("(update_visu.c) TTF_OpenFont : ", d);
	d->mod.x = 1980;
	d->mod.y = 880 + 20 - (880 / 3);
	d->mod.w = 540;
	d->mod.h = (880 / 3) - 20;
	if (SDL_RenderCopy(d->rend, d->f_tmp, NULL, &d->mod) < 0)
		error("(update_visu.c) SDL_RenderCopy : ", d);
	d->mod.y = 880 + 27 - (880 / 3) + 15;
	i = 0;
	update_info_op2(d, a, info, i);
}
