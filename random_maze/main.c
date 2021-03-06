//
//  main.c
//  Algorithm Project21
//
//  Created by Woongsup Kim on 2021/11/10.
//

/*
CELLS, MAZE, initialize(), break_wall(), show_maze()은 기존과 동일함.
CELL_WIDTH와 CELL_HEIGHT을 10으로 매크로 정의함

int check_complete(int i, int j) 추가
void dfs(int i, int j) 수정
main()에 srand(time(NULL)); 추가

int check_complete(int i, int j)
->  i행 j열 위치를 기준으로 상하좌우가 모두 탐색 완료되었는지 확인하는 함수.	탐색이 완료되지 않았다면 0을 반환하고, 탐색이 완료되었다면 1을 반환함.

void dfs(int i, int j)
->	1. i행 j열을 방문했다는 표시를 함
	2. while문으로 상하좌우가 모두 탐색 될 때까지 반복함.
	3. direction에 rand() % 4을 사용해 0~3의 숫자를 랜덤으로 대입함.
	4. 0~3까지 LEFT, RIGHT, UP, DOWN 매크로 정의 되어 있으므로, direction 값과 비교해서 방향을 결정함.
	5. 해당 방향이 이미 탐색되었다면 다시 반복문으로 랜덤 방향을 정하고, 탐색되지 않았다면 MAZE[] 배열을 수정해 현재 위치와 다음 위치 사이의 벽을 없애버림.
	6. 재귀호출로 해당 방향의 위치에서 dfs를 호출함.

int main(int argc, const char *argv[])
->	srand(time(NULL));을 추가함. srand함수는 rand함수의 seed를 바꿔주어 매번 다른 난수를 발생시킬 수 있게함. 따라서 time함수를 사용해 시간을 seed로 주어 매번 다른 난수를 생성하게 함.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// set the maze width and size
#define CELL_WIDTH 10
#define CELL_HEIGHT 10

// move direction
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

// Array for the maze cells
// CELLS[i][j] is ith row and jth column cell in in the maze.
// if the cell of ith row and jth column is visited, then CELLS[i][j] = 1.
// Otherwise CELLS[i][j] = 0
int CELLS[CELL_HEIGHT][CELL_WIDTH];

// Array for maze with walls.
// For any route in the maze, the corresponding walls are marked to '0'.
// Otherwise ' '.
char MAZE[2*CELL_HEIGHT+1][4*CELL_WIDTH+2];

// Initialization. MAZE cells are set to 0 (unvisited).
// Maze walls are also initialized. See the project document.
void initialize(void) {
    int i = 0;
    int j = 0;

    // initialize CELLS
    // All the entries of CELL array is set to 0 (unvisited).
    for(i = 0; i < CELL_HEIGHT; i++)
        for(j = 0; j < CELL_WIDTH; j++)
            CELLS[i][j] = 0;

    // initialize the maze.
    // WALL is set to '0'.
    // Empty space is set to ' '.
    for(i = 0; i < 2*CELL_HEIGHT+1; i++) {
        for(j = 0; j < 4*CELL_WIDTH+1; j++) {
            if(i%2 == 0)
                MAZE[i][j] = '0';
            else
                if(j%4 == 0)
                    MAZE[i][j] = '0';
                else
                    MAZE[i][j] = ' ';

        }
        MAZE[i][j] = '\0';
    }
}

// check cells
int	check_complete(int i, int j) {
	if (i != 0 && CELLS[i-1][j] == 0)
		return (0);
	if (i != CELL_HEIGHT-1 && CELLS[i+1][j] == 0)
		return (0);
	if (j != 0 && CELLS[i][j-1] == 0)
		return (0);
	if (j != CELL_WIDTH-1 && CELLS[i][j+1] == 0)
		return (0);
	return (1);
}

// run dfs for break walls.
void dfs(int i, int j) {

	CELLS[i][j] = 1; // mark CELLS[i][j] as visited.
	while (1) {
		if (check_complete(i, j))
			break ;
		int direction = rand() % 4;
		// if CELLS[i-1][j] is unvisited, then break the up-side wall.
		if(direction == UP && i != 0) // unless the cell is located in the top,
			if(CELLS[i-1][j] == 0) {
				MAZE[i*2][j*4+1] = ' ';
				MAZE[i*2][j*4+2] = ' ';
				MAZE[i*2][j*4+3] = ' ';
				dfs(i-1,j);
			}
		// if CELLS[i+1][j] is unvisited, then break the down-side wall.
		if(direction == DOWN && i != CELL_HEIGHT-1) // unless the cell is located in the bottom,
			if(CELLS[i+1][j] == 0) {
				MAZE[i*2+2][j*4+1] = ' ';
				MAZE[i*2+2][j*4+2] = ' ';
				MAZE[i*2+2][j*4+3] = ' ';
				dfs(i+1,j);
			}
		// if CELLS[i][j-1] is unvisited, then break the left-side wall.
		if(direction == LEFT && j != 0)
			if(CELLS[i][j-1] == 0) {
				MAZE[i*2+1][j*4] = ' ';

				dfs(i,j-1);
			}
		// if CELLS[i][j+1] is unvisited, then break the right-side wall.
		if(direction == RIGHT && j != CELL_WIDTH-1)
			if(CELLS[i][j+1] == 0) {
				MAZE[i*2+1][j*4+4] = ' ';
				dfs(i,j+1);
			}
	}

// }
}

// break walls from the initial maze through dfs.
void break_wall(void) {
    dfs(0,0);
}

// show the maze image to the screen.
void show_maze(void) {
    int i;

    for(i = 0; i < CELL_HEIGHT*2+1; i++)
        printf("%s\n", MAZE[i]);

}


int main(int argc, const char * argv[]) {

	srand(time(NULL));
    initialize();
    break_wall();
    //show the 1st randomly created maze
    printf("Draw the first maze \n\n");
    show_maze();
    //draw and show the 2nd randomly created maze
    initialize();
    break_wall();
    printf("\nDraw the second maze \n\n");
    show_maze();
    //draw and show the 3rd randomly created maze
    initialize();
    break_wall();
    printf("\nDraw the third maze \n\n");
    show_maze();

    return 0;
}

