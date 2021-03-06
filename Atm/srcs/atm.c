#include "atm.h"

void    insert_person(machine *atm, int time)
{
	person *parsing;

	atm->cnt_waiting++;
	person *man = (person *)malloc(sizeof(person));
	init_person(man, time);

	if (man->vip || atm->next_p == NULL)
	{
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
}

int		in_atm(machine *atm)
{
	if (atm->working == 0)
		return (0);
	return (1);
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
		if (parsing->cnt_waiting + in_atm(parsing) < min)
		{
			overlap = 0;
			min = parsing->cnt_waiting + in_atm(parsing);
			atm_min[overlap] = parsing;
		}
		else if(parsing->cnt_waiting + in_atm(parsing) == min)
		{
			overlap++;
			atm_min[overlap] = parsing;
		}
		parsing = parsing->next_a;
	}
	if (overlap > 0)
	{
		if (overlap == 1)
		{
			parsing = atm_min[rand()%2];
			return (parsing);
		}
		parsing = atm_min[rand()%3];
		return (parsing);
	}
	parsing = atm_min[overlap];
	return (parsing);
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

void	print_working(machine *atm, int t, int *complete_nbr, int *average_nbr)
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
					printf("9시 %d분 - %d번 고객(%d분 소요)이 %d번 ATM기에서 서비스를 시작함\n", t, man->entrance, man->time, parsing->index);
				else
					printf("10시 %d분 - %d번 고객(%d분 소요)이 %d번 ATM기에서 서비스를 시작함\n", t - 60, man->entrance, man->time, parsing->index);
				(*complete_nbr)++;
				*average_nbr += t - man->entrance;
				parsing->cnt_waiting--;
				parsing->working = man->time;
				parsing->next_p = man->next_p;
				free(man);
			}
		}
		parsing = parsing->next_a;
	}
}
