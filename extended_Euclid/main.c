#include <stdio.h>	// scanf, printf 사용하려고 include
#include <stdlib.h>	// malloc 사용하려고 include

struct _node	// x, y, c를 저장하는 구조체
{
	int	first;	// x값
	int	second;	// y값
	int	third;	// c값
};

struct _node	*extended_Euclid(int a, int b)	// 확장 유클리드 함수
{
	struct _node	*n1, *n2;	// 구조체를 가르키는 포인터 변수

	n1 = (struct _node *)malloc(sizeof(struct _node));	// 구조체 만들어서 n1에 담음.
	if (b == 0)		// 계속 재귀하다가 b가 0이 될 때 (재귀함수 탈출 조건)
	{
		n1->first = 1;
		n1->second = 0;
		n1->third = a;
		return (n1);
	}
	else		// b가 0이 아니면
	{
		n2 = extended_Euclid(b, a % b);		// 재귀를해서 나온 값을 n2에 담음.
		n1->first = n2->second;		// n1 값 설정
		n1->second = n2->first - ((a / b) * n2->second);
		n1->third = n2->third;
		free(n2);		// 이제 쓸모 없으니 메모리 해제
		return (n1);		// n1 반환
	}
}

int	main(void)
{
	struct	_node *n;
	int		a;
	int		b;

	while (1)
	{
		printf("\n\n Type two positive integers -> ");
		scanf("%d %d", &a, &b);
		if (a < 0 || b < 0)		// 잘못된 입력값
		{
			printf("invalid input\n");
			continue ;
		}
		else if (a == 0 || b == 0)	// a나 b중 하나가 0인 경우
		{
			break ;		// 종료
		}
		n = extended_Euclid(a, b);	// 재귀 호출해서 나온 값을 n에 담음
		printf("x is %d, y is %d, and c is %d\n", n->first, n->second, n->third);
		free(n);		// 사용끝난 구조체 해제
		break ;
	}
	return (0);
}
