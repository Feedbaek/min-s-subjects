#include "atm.h"

int		main(void)
{
	machine		atm_1, atm_2, atm_3;
	machine		*atm;

	init_machine(&atm_1, &atm_2, &atm_3);
	for (int i = 0; i < 120; i++)
	{
		person man;
		init_person(&man, i);
		working_atm(&atm_1);
		atm = choose_atm(&atm_1);
		insert_person(atm, &man);
		print_working(atm, i);
	}

	return (0);
}
