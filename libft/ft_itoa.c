/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeutsch <sdeutsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:39:04 by sdeutsch          #+#    #+#             */
/*   Updated: 2023/11/17 17:19:03 by sdeutsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_len_nb(long	int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_implement_dest(char *dest, int n, long int nbr, int len_nb)
{
	int	len_tot;

	len_tot = len_nb;
	if (n > 0)
	{
		while (nbr > 0)
		{
			dest[len_nb - 1] = (nbr % 10) + '0';
			len_nb--;
			nbr = nbr / 10;
		}
		dest[len_tot] = '\0';
	}
	if (n < 0)
	{
		dest[0] = 45;
		while (nbr > 0)
		{
			dest[len_nb] = (nbr % 10) + '0';
			len_nb--;
			nbr = nbr / 10;
		}
		dest[len_tot + 1] = '\0';
	}
	return (dest);
}

char	*ft_implement_dest_bis(char *dest, long int nbr)
{
	if (nbr == 0)
	{
		dest[0] = '0';
		dest[1] = '\0';
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	long int	nbr;
	int			len_nb;				
	char		*dest;

	nbr = n;
	if (n < 0)
	{
		nbr = -nbr;
		len_nb = ft_len_nb(nbr);
		dest = malloc((len_nb + 2) * sizeof (char));
		if (!dest)
			return (NULL);
	}
	else
	{
		len_nb = ft_len_nb(nbr);
		dest = malloc((len_nb + 1) * sizeof (char));
		if (!dest)
			return (NULL);
	}
	if (nbr == 0)
		dest = ft_implement_dest_bis(dest, nbr);
	else
		dest = ft_implement_dest(dest, n, nbr, len_nb);
	return (dest);
}

// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	int		n;
// 	char	*dest;

// 	n = atoi(av[1]);
// 	dest = ft_itoa(n);

// 	printf("%s\n", dest);
// 	return 0;
// }