#include "atm.h"

void	init_machine(machine *atm)
{
	atm->working = 0;
	atm->cnt_waiting = 0;
	atm->next = NULL;
}

void	insert_person(machine *atm, person *man)
{
	machine *parsing;
	if (man->vip)
	{
		man->next = atm->next;
		atm->next = man;
	}
	else
	{
		parsing = atm;
		while (parsing->next)
			parsing = parsing->next;
		parsing->next = man;
	}
}

int		main(void)
{
	machine atm_1, atm_2, atm_3;
	
	for (int i = 0; i < 120; i++)
	{
		
	}
	return (0);
}
