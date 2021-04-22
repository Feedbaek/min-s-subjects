#include "atm.h"

int		main(void)
{
	machine		atm_1, atm_2, atm_3;
	machine		*atm;

	int total_nbr = 0, complete_nbr = 0, average_waiting = 0, current_waiting = 0;
	srand(time(NULL));
	init_machine(&atm_1, &atm_2, &atm_3);
	for (int i = 0; i < 120; i++)
	{
		delete_prime(&atm_1, i, &total_nbr, &average_waiting);
		working_atm(&atm_1);
		atm = choose_atm(&atm_1);
		insert_person(atm, i);
		print_working(atm, i, &complete_nbr, &average_waiting);
	}
	total_nbr += complete_nbr;
	average_waiting /= total_nbr;
	current_waiting = 120 - total_nbr;
	printf("업무를 본 총 고객 수: %d\n", complete_nbr);
	printf("줄에서 기다린 평균 시간: %d\n", average_waiting);
	printf("10시 59분 기다리고 있는 고객 수: %d\n", current_waiting);
	return (0);
}
