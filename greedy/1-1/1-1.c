#include <stdio.h>	// pritf
#include <string.h>	// strtok
#include <stdlib.h>	// atoi
#define MAX_LEN 100	// 최대 문자열 길이

int	main(void)
{
	char	str[MAX_LEN];
	char	*ptr;
	int		bottle;	// 물병 크기
	int		cup_300;
	int		cup_500;
	int		remainder;
	int		min;
	FILE*	fs;	// 입력파일 받을 변수

	if ((fs = fopen("input.txt", "r")) == NULL)	// 파일 읽기모드로 열기
	{
		printf(">> input.txt 에러\n");
		return (-1);	// 에러시 종료
	}

	fgets(str, MAX_LEN, fs); // MAX_LEN 만큼 fs파일 읽어서 str에 저장

	ptr = strtok(str, " ");	// strtok 함수를 사용해 공백을 기준으로 숫자 읽음
	while (ptr != NULL)	// 문자열 끝날 때 까지 반복
	{
		bottle = atoi(ptr);	// 문자열을 정수형으로 바꿈  ex) "100" => 100
		min = -1;	// 초기값 세팅
		for (int i = bottle / 500; i >= 0; i--)
		{
			remainder = bottle - (500 * i);
			if (remainder % 300 == 0)
			{
			// cup_*00 = *00ml 컵 사용 횟수
				cup_300 = (remainder) / 300;
				cup_500 = i;
				if (bottle - (cup_500 * 500) - (cup_300 * 300) == 0)	// 물통의 용량을 정확히 채울 수 있다면
					if (min < 0 || cup_300 + cup_500 < min)	// 최소 값인지 확인
						min = cup_300 + cup_500;
			}
		}
		printf("%d ", min);
		ptr = strtok(NULL, " ");	// 다음 숫자 읽기
	}
	printf("\n");
	fclose(fs);
}
