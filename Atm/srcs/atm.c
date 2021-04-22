#include "atm.h"

void    insert_person(machine *atm, int time)
{
	person *man = (person *)malloc(sizeof(person));
	init_person(man, time);
	person *parsing;
	if (man->vip || atm->next_p == NULL)
	{
		if (man->vip)
		man->next_p = atm->next_p;
		atm->next_p = man;
	} 
	else
	{
		parsing = atm->next_p;
		while (parsing->next_p)
			parsing = parsing->next_p;
		parsing->next_p = man;
	}
	atm->cnt_waiting++;
}

machine         *choose_atm(machine *atm)
{
	int     min;
	int     overlap;
	machine *parsing;
	machine *atm_min[3];

 	overlap = 0;
	parsing = atm;
	min = 120;
	for (int i = 0; i < 3; i++)
	{
		if (parsing->cnt_waiting < min)
		{
			overlap = 0;
			min = parsing->cnt_waiting;
			atm_min[overlap] = parsing;
		}
		else    if (parsing->cnt_waiting == min)
		{
			overlap++;
			if (overlap == 1)
				atm_min[overlap] = parsing;
			else
				atm_min[overlap] = parsing;
		}
		parsing = parsing->next_a;
	}
	if (overlap > 0)
	{
		if (overlap == 1)
			return (atm_min[rand()%2]);
		return (atm_min[rand()%3]);
	}
	return (atm_min[overlap]);
}

void	working_atm(machine *atm)
{
	machine *parsing;
	
	parsing = atm;
	for (int i = 0; i < 3; i++)
	{
		if (parsing->working > 0)
			parsing->working--;
		parsing = parsing->next_a;
	}
}

void	print_working(machine *atm, int t)
{
	machine *parsing;
	person	*man;

	parsing = atm;
	for (int i = 0; i < 3; i++)
	{
		man = parsing->next_p;
		if (parsing->working == 0)
		{
			if (man)
			{
				if (t < 60)
					printf("9시 %d분 -%d번 고객(%d분 소요)이 %d번 ATM기에서 서비스를 시작함\n", t, man->entrance, man->time, parsing->index);
				else
					printf("10시 %d분 -%d번 고객(%d분 소요)이 %d번 ATM기에서 서비스를 시작함\n", t - 60, man->entrance, man->time, parsing->index);
				parsing->working = man->time;
				parsing->next_p = man->next_p;
				free(man);
			}
		}
		parsing = parsing->next_a;
	}
}
