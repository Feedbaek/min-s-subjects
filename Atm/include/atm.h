#ifndef ATM_H
# define ATM_H

#include <stdio.h>
#include <stdlib.h>

typedef struct waiting_line
{
	int entrance;
	int time;
	int vip;
	struct waiting_line *next;
} person;

typedef struct atm_machine
{
	int working;
	int cnt_waiting;
	struct waiting_line *next;
} machine;
#endif
