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
     	person* person_c;
     	person* person_n;
     	parsing = atm;
     	for (int i = 0; i < 3; i++)
     	{
	  	person_c = parsing->next_p;
	  	if (person_c == NULL)
		{
			parsing = parsing->next_a;
	       		continue;
		}
	  	if (time % 10 == 0)
	  	{
	       		if (is_prime(person_c->entrance) == 1)
	       		{
		    		parsing->next_p = person_c->next_p;
		    		printf("%d번 고객이 탈주했습니다.\n", person_c->entrance);
				*average_nbr += time - person_c->entrance;
				free(person_c);
				*total_nbr = *total_nbr + 1;
	       		}
	       		person_n = person_c->next_p;
	       		while (person_n != NULL)
	       		{
		    		if (is_prime(person_n->entrance) == 1)
		    		{
					person_c->next_p = person_n->next_p;
			 		printf("%d번 고객이 탈주했습니다.\n",person_n->entrance);
					*average_nbr += time - person_c->entrance;
					free(person_n);
					*total_nbr = *total_nbr + 1;
			 		person_n = person_c->next_p;
			 		continue;
		    		}
		    		person_c = person_c->next_p;
		    		person_n = person_c->next_p;
	       		}
	  	}
	  	parsing = parsing->next_a;
     	}
}
