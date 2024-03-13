

#include "libft.h"
#include <stdlib.h>



int	main()
{

	void	*p;
	int		*p2;

	p = NULL;

	p2 = malloc(sizeof(int));
	ft_dprintf(2, "hello\n");
	ft_dprintf(2, "c = [%c]\n", '$');
	ft_dprintf(2, "s = [%s]\n", "The quick brown foxruns over the lazy dog");
	ft_dprintf(2, "null = [%s]\n", (char *)0);
	ft_dprintf(2, "i = [%i]\n", -42);
	ft_dprintf(2, "d = [%d]\n", -42);
	ft_dprintf(2, "u = [%u]\n", 123456789);
	ft_dprintf(2, "x = [%x]\n", 0xFF00AA);
	ft_dprintf(2, "X = [%X]\n", 0xFF00AA);
	ft_dprintf(2, "p = [%p]\n",p);
	ft_dprintf(2, "p2 = [%p]\n",p2);
	free(p2);


}
