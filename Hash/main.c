#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TABLE_SIZE 541
#define NAME_SIZE 20
#define EMPTY 0
#define FALSE 0
#define TRUE 1

struct hash
{
	char names[NAME_SIZE]; // store inserted data
	unsigned short collision; // check collision for the data
};

struct hash hash_table[TABLE_SIZE];

void initialize_table() // 해쉬 테이블을 초기화한다.
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		strcpy(hash_table[i].names,"");
		hash_table[i].collision = 0;
	}
}

int hash1(char str[])
{
	int i,h;

	for(i=0,h=0; i < strlen(str); i++)
	{
		h = ((int)str[i] + h)%TABLE_SIZE;
	}
	return h;
}

int	main(void)
{
	const int max = 1024;
	char line[max];
	char *pLine;
	FILE *in = fopen("names.txt", "r");
	while (pLine = fgets(line, max, in))
	{
		printf("%s", pLine);
	}
	fclose(in);
	return (0);
}
