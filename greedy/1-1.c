#include <stdio.h>	// pritf
#include <string.h>	// strtok
#include <stdlib.h>	// atoi
#define MAX_LEN 100	// 최대 문자열 길이

int	main(void)
{
	char	str[MAX_LEN + 1];
	char	*ptr;
	int		bottle;	// 물병 크기
	int		cup_300;
	int		cup_500;

	FILE* fs;	// 입력파일 받을 변수
	fs = fopen("input.txt", "r");	// 파일 읽기모드로 열기

	fgets(str, MAX_LEN, fs); // MAX_LEN 만큼 fs파일 읽어서 str에 저장
	str[MAX_LEN] = 0;	// 문자열 끝에는 null 문자 넣기

	ptr = strtok(str, " ");	// strtok 함수를 사용해 공백을 기준으로 숫자 읽음
	while (ptr != NULL)	// 문자열 끝날 때 까지 반복
	{

		ptr = strtok(NULL, " ");	// 다음 숫자 읽기
	}
	for (int i = (bottle / 500); i >= 0; i--) {
	if (( ) % 300 == 0) {
	// cup_*00 = *00ml 컵 사용 횟수
	cup_300 = ( ) / 300
	cup_500 = ( )
	}
	}
	print(cup_300 + cup_500)
}
