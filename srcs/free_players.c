#include "corewar.h"

void free_players(t_player *player, int nb_players)
{
	int i;

	i = 0;
	while(i < nb_players)
	{
		free(player[i].content);
		free(player[i].name);
		free(player[i].prog);
		free(player[i].comment);
		i++;
	}
	free(player);
}