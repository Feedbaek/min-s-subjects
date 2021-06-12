#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_VERTICES 100
#define INF 1000
#define TRUE 1
#define FALSE 0

int parent[MAX_VERTICES];


struct Edge {
   int start, end, weight;
};
typedef struct GraphType {
   int n;
   struct Edge edges[2 * MAX_VERTICES];
} GraphType;

