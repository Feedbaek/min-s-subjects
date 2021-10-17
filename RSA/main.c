#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MESSAGE_LENGTH 35

char message[] = {'H','e','l','l','o',',',' ','P','l','e','a','s','e',' ','l','o','v','e',' ','W','o','o','n','g','s','u','p','!','!', '!','\0'};
unsigned int encryption[MESSAGE_LENGTH];
char decryption[MESSAGE_LENGTH];

struct _node {
	int first;
	int second;
	int third;
};

struct _node	*extended_Euclid(int a, int b)
{
	struct _node	*n1, *n2;

	n1 = (struct _node *)malloc(sizeof(struct _node));
	if (b == 0)
	{
		n1->first = 1;
		n1->second = 0;
		n1->third = a;
		return (n1);
	}
	else
	{
		n2 = extended_Euclid(b, a % b);
		n1->first = n2->second;
		n1->second = n2->first - ((a / b) * n2->second);
		n1->third = n2->third;
		free(n2);
		return (n1);
	}
}

unsigned int do_exp(int c, int key, int N){
	unsigned int	prod = 1;

	for (int i=0; i < key; i++)
		prod = (prod * c) % N;
	return prod;
}

void print_encryption(int e[]) {
	for (int i = 0; i < MESSAGE_LENGTH; i++)
		printf("%d", e[i]);
	printf("\n");
}

int	main(void)
{
	int	p;
	int	q;
	int	N;
	int	e;
	int	d;
	int	oil;
	struct _node	*node;

	printf("임의의 소수 p와 q를 입력하시오.\n");	// 소수의 값이 클 수록 정확
	scanf("%d %d", &p, &q);		// 해보니까 (p * q)값이 작으면 잘 안됨
	N = p * q;
	oil = (p-1) * (q-1);
	for (int i=2; i<N; i++)	// e 값 정하기
	{
		node = extended_Euclid(oil, i);
		if (node->third == 1)
		{
			e = i;
			free(node);
			break ;
		}
		free(node);
	}
	for (int i=1; i <oil; i++)	// d 값 구하기
	{
		if ((e * i) % oil == 1)
		{
			d = i;
			break ;
		}
	}
	for (int i=0; i < MESSAGE_LENGTH; i++)
		encryption[i] = do_exp(message[i], e, N);
	print_encryption(encryption);
	for (int i=0; i < MESSAGE_LENGTH; i++)
		decryption[i] = (char)do_exp(encryption[i], d, N);
	printf("%s", decryption);
	return (0);
}
