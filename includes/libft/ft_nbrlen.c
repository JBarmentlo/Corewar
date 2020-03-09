/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoursol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 11:01:34 by ncoursol          #+#    #+#             */
/*   Updated: 2020/03/09 11:01:59 by ncoursol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t		ft_nbrlen(int nbr)
{
    int		len;

    len = 0;
    if (nbr == 0)
        return (1);
    if (nbr < len)
        len += 1;
    while (nbr != 0)
    {
        nbr = nbr / 10;
        len++;
    }
    return (len);
}
