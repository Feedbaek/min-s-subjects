#include "atm.h"

void	rec_free(person *man)
{
	printf("다음 대기사람: %d\n", man->entrance);
	if (man->next_p)
		rec_free(man->next_p);
	//free(man);
}

void	atm_free(machine *atm)
{
	person *parsing;
	for (int i = 0; i < 3; i++)
	{
		printf("atm%d 현재 대기 수: %d\n", atm->index, atm->cnt_waiting); 
		parsing = atm->next_p;
		if (parsing)
			printf("대기 사람: %d\n", parsing->entrance);
		else
		{
			atm = atm->next_a;
			continue ;
		}
		if (parsing->next_p)
			rec_free(parsing->next_p);
		//free(parsing);
		atm = atm->next_a;
	}
}

int		main(void)
{
	machine		*atm_1, *atm_2, *atm_3;
	machine		*atm;

	atm_1 = (machine *)malloc(sizeof(machine));
	atm_2 = (machine *)malloc(sizeof(machine));
	atm_3 = (machine *)malloc(sizeof(machine));

	int total_nbr = 0, complete_nbr = 0, average_waiting = 0, current_waiting = 0;
	
	srand(time(NULL));
	init_machine(atm_1, atm_2, atm_3);
	for (int i = 0; i < 120; i++)
	{
		working_atm(atm_1);
		atm = choose_atm(atm_1);
		insert_person(atm, i);
		print_working(atm, i, &complete_nbr, &average_waiting);
		delete_prime(atm_1, i, &total_nbr, &average_waiting);
		if (i % 10 == 0)
		{
			current_waiting = atm_1->cnt_waiting + atm_2->cnt_waiting + atm_3->cnt_waiting;
	 		printf("현재 기다리고 있는 고객 수: %d\n", current_waiting);
			atm_free(atm);	
		}
		printf("=================\n");
	}
	total_nbr += complete_nbr;
	average_waiting /= total_nbr;
	current_waiting = atm_1->cnt_waiting + atm_2->cnt_waiting + atm_3->cnt_waiting;
	printf("업무를 본 총 고객 수: %d\n", complete_nbr);
	printf("줄에서 기다린 평균 시간: %d\n", average_waiting);
	printf("10시 59분 기다리고 있는 고객 수: %d\n", current_waiting);
	atm_free(atm);
	free(atm_1);
	free(atm_2);
	free(atm_3);
	return (0);
}
