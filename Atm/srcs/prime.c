#include "atm.h"

int      is_prime(int e)
{
     	if (e <= 1)
	  	return (0);
     	if (e == 2)
	  	return (1);
     	for (int i = 2; i < e; i++)
     	{
	  	if (e % i == 0)
	       		return(0);
     	}
     	return (1);
}

void   delete_prime(machine* atm,int time, int *total_nbr, int *average_nbr) 
{
     	machine* parsing;
     	person* man;
     	person* next_man;
     	parsing = atm;
     	for (int i = 0; i < 3; i++)
     	{
	  	man = parsing->next_p;
	  	if (man == NULL)
		{
			parsing = parsing->next_a;
	       		continue;
		}
	  	if (time % 10 == 0)
	  	{
	       		while (man != NULL && is_prime(man->entrance))
	       		{
		    		parsing->next_p = man->next_p;
				*average_nbr += time - man->entrance;
				(*total_nbr)++;
				parsing->cnt_waiting--;
				free(man);
				man = parsing->next_p;
	       		}
			if (man == NULL)
			{
				parsing = parsing->next_a;
				continue;
			}
			next_man = man->next_p;
	       		while (next_man != NULL)
	       		{
		    		if (is_prime(next_man->entrance))
		    		{
					man->next_p = next_man->next_p;
					*average_nbr += time - next_man->entrance;
					(*total_nbr)++;
					parsing->cnt_waiting--;
					free(next_man);
			 		next_man = man->next_p;
			 		continue;
		    		}
		    		man = next_man;
		    		next_man = man->next_p;
	       		}
	  	}
	  	parsing = parsing->next_a;
     	}
}
