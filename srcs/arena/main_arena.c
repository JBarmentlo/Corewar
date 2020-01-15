#include "arena.h"

#include "stdio.h"

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_disp		d;
	t_arena		a;
	int			running;
  
	a.nb_champions = 3;
	a.champion_table[3].name = "Jjaegle";
	a.champion_table[2].name = "Jbarment";
	a.champion_table[1].name = "Ncoursol";
	a.champion_table[0].name = "Dberger";
		
	init_window(&d, a);
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
}

