#ifndef ATM_H
# define ATM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct waiting_line
{
	int entrance;
	int time;
	int vip;
	struct waiting_line *next_p;
} person;                        // 사람 구조체

typedef struct atm_machine
{
	int index;
	int working;
	int cnt_waiting;
	struct atm_machine *next_a;
	struct waiting_line *next_p;
} machine;                       //  atm 구조체

void    init_machine_data(machine *atm, int i);
void    init_machine(machine *atm_1, machine *atm_2, machine *atm_3);
void    init_person(person *man, int t);

void    insert_person(machine *atm, int time);
machine         *choose_atm(machine *atm);
void    working_atm(machine *atm);
void    print_working(machine *atm, int time);

#endif
