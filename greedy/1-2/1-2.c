#include <stdio.h>	// printf
#include <string.h>	// strtok
#include <stdlib.h>	// atoi
#include <stdlib.h>	// calloc
#define MAX_LEN 100	// 최대 문자열 길이

typedef	struct	s_line	// 연결리스트 구조체 정의
{
	int	start;
	int	end;
	int	len;
}	line;

int	main(void)
{
	char	str[MAX_LEN];	// 입력파일 문자열 저장변수
	char	*ptr;	// 공백기준으로 읽은 문자열
	char	*base_line;	// 선분들을 올리는 직선
	FILE*	fs;	// 입력파일 받을 변수
	int		idx;	// 전체 선분들의 개수
	int		cnt;	// 최대한 직선에 올린 선분 개수
	int		line_len;	// 직선의 길이
	line	list[MAX_LEN];	// 선분들을 저장하는 배열
	line	tmp;	// 버블 정렬에 사용하는 변수

	if ((fs = fopen("input.txt", "r")) == NULL)	// 파일 읽기모드로 열기
	{
		printf(">> input.txt 에러\n");
		return (-1);	// 에러시 종료
	}

	fgets(str, MAX_LEN, fs); // MAX_LEN 만큼 fs파일 읽어서 str에 저장
	ptr = strtok(str, " ");	// strtok 함수를 사용해 공백을 기준으로 숫자 읽음

	idx = 0;
	line_len = 0;
	while (ptr != NULL)	// 문자열 끝날 때 까지 반복
	{
		list[idx].start = atoi(ptr);
		ptr = strtok(NULL, " ");	// 다음 숫자 읽기
		list[idx].end = atoi(ptr);
		if (line_len < list[idx].end)
			line_len = list[idx].end;
		list[idx].len = list[idx].end - list[idx].start;
		ptr = strtok(NULL, " ");	// 다음 숫자 읽기
		idx++;
	}

	for (int i=0; i<idx-1; i++)	// 버블 정렬로 길이 오름차순 정렬
	{
		for (int j=0; j<idx-i-1; j++)
		{
			if (list[j].len > list[j+1].len)
			{
				tmp = list[j];
				list[j] = list[j+1];
				list[j+1] = tmp;
			}
		}
	}

	cnt = 0;
	base_line = (char *)calloc(line_len, sizeof(char));	// 직선을 0으로 초기화
	for (int i=0; i<idx; i++)
	{
		int	flag = 0;	// 겹치는지 체크하는 플래그
		for (int j=list[i].start-1; j<list[i].end-1; j++)	// 겹치는지 확인
		{
			if (base_line[j] == 1)	// 겹치면
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)	// 안겹치면
		{
			cnt++;
			for (int j=list[i].start-1; j<list[i].end-1; j++)
				base_line[j] = 1;
		}
	}
	printf("%d\n", cnt);
	return (0);
}
