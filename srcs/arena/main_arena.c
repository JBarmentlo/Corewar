#include "arena.h"

#include "stdio.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	/*

	t_disp		d;
	int			running;

	init_window(&d);
	running = 1;
	while (running)
	{
		while (SDL_PollEvent(&d.event))
			if (d.event.type == SDL_QUIT
					|| d.event.key.keysym.sym == SDLK_ESCAPE)
				running = 0;
	}
	error("End.", &d);
	return (0);
	*/
	uint16_t a;

	a = 3;
	bit_dump(&a, 2);
	return (0);
}
