#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MESSAGE_LENGTH 30 // 35였는데 문자열 길이가 30이라 고침
// Hello, Please, love Woongsup! 에 대한 문자열 정의
char message[] = {'H','e','l','l','o',',',' ','P','l','e','a','s','e',' ','l','o','v','e',' ','W','o','o','n','g','s','u','p','!','!', '!','\0'};
// 암호화된 문자들은 정수형 배열인 encryption에 저장한다.
unsigned int encryption[MESSAGE_LENGTH];
// 복호화된 문자들은 문자형 배열인 decryption에 저장한다.
char decryption[MESSAGE_LENGTH];

// extended_Euclid 함수 사용을 위한 구조체
struct _node {
	int first;
	int second;
	int third;
};

struct _node	*extended_Euclid(int a, int b)	// 확장 유클리드 함수
{
	struct _node	*n1, *n2;	// 구조체를 가르키는 포인터 변수

	n1 = (struct _node *)malloc(sizeof(struct _node));	// 구조체 만들어서 n1에 할당.
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
// ckey mod N 값을 구한다.
// 아래함수의 매개변수 key는 암호화할 때는 공개키 (e,N)의
//e 값이며 할 때는 복호화 할 때에는 비밀키 (d, N)의 d값을 의미한다.

//do_exp()는 ckey mod N 로 계산 해준 값을 리턴한다.
//단 c를 key 번 곱하게 되면 그 값이 정수형으로 감당할 수 없을
//정도로 커지므로 c를 곱해줄 때 마다 mod 연산 (%연산)을
//구행하여 그 값을 충분히 작은 값으로 유지시킬 필요가 있다.
//물론 수업시간에 배운 내용을 적용하여 ckey mod N을 구할 수도
//있다.
unsigned int do_exp(int c, int key, int N){
	unsigned int	prod = 1;
	for (int i=0; i < key; i++)
		prod = (prod * c) % N;
	return prod; // ckey mod N을 리턴
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

	printf("임의의 소수 p와 q를 입력하시오.\n");
	scanf("%d %d", &p, &q);
	N = p * q;
	oil = (p-1) * (q-1);
	for (int i=2; i<oil; i++)
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
	for (int i=1; i < oil; i++)
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
