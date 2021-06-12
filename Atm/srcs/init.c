#include "atm.h"

void	init_machine_data(machine *atm, int i)
{
	atm->index = i;
	atm->working = 0;
	atm->cnt_waiting = 0;
	atm->next_p = NULL;
}

void	init_machine(machine *atm_1, machine *atm_2, machine *atm_3)
{
	init_machine_data(atm_1, 1);
	init_machine_data(atm_2, 2);
	init_machine_data(atm_3, 3);
	atm_1->next_a = atm_2;
	atm_2->next_a = atm_3;
	atm_3->next_a = atm_1;
}

void	init_person(person *man, int t)
{
	man->entrance = t;
	man->time = rand() % 9 + 2;
	man->vip = 0;
	if (rand() % 10 == 1)
		man->vip = 1;
	man->next_p = NULL;
}
