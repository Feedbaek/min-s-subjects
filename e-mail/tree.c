#include "tree.h"

void set_init(int n) {
   for (int i = 0; i < n; i++)
      parent[i] = -1;
}
int set_find(int curr) {
   if (parent[curr] == -1)
      return curr;
   while (parent[curr] != -1) curr = parent[curr];
   return curr;
}
void set_union(int a, int b) {
   int root1 = set_find(a);
   int root2 = set_find(b);
   if (root1 != root2)
      parent[root1] = root2;
}
void graph_init(GraphType* g)
{
   g->n = 0;
   for (int i = 0; i < 2 * MAX_VERTICES; i++) {
      g->edges[i].start = 0;
      g->edges[i].end = 0;
      g->edges[i].weight = INF;
   }
}
void insert_edge(GraphType* g, int start, int end, int w)
{
   g->edges[g->n].start = start;
   g->edges[g->n].end = end;
   g->edges[g->n].weight = w;
   g->n++;
}
int compare(const void* a, const void* b) {
   struct Edge* x = (struct Edge*)a;
   struct Edge* y = (struct Edge*)b;
   return (y->weight - x->weight);
}

void map_init(struct Edge *map, int max)
{
	int i = 0;

	while (i < max)
	{
		map[i].start = -1;
		map[i].end = -1;
		map[i].weight = INF;
		i++;
	}
}

void make_map(struct Edge *map, int start, int end, int weight, int i)
{
	map[i].start = start;
	map[i].end = end;
	map[i].weight = weight;
}

int kruskal(GraphType* g, struct Edge *map) {
   int edge_accepted = 0;
   int uset, vset;
   struct Edge e;

   set_init(g->n);
   qsort(g->edges, g->n, sizeof(struct Edge), compare);

   int i = 0;
   while (i < (g->n - 1)) {
      e = g->edges[i];
      uset = set_find(e.start);
      vset = set_find(e.end);
      if (uset != vset) {
         set_union(uset, vset);
		 make_map(map, e.start, e.end, e.weight, edge_accepted);
         edge_accepted++;
      }
      i++;
   }
	return (edge_accepted);
}
void g_set(GraphType*g){
   insert_edge(g, 0, 1, 19);
   insert_edge(g, 0, 2, 3);
   insert_edge(g, 0, 3, 11);
   insert_edge(g, 0, 4, 13);
   insert_edge(g, 1, 2, 4);
   insert_edge(g, 1, 3, 5);
   insert_edge(g, 2, 3, 8);
   insert_edge(g, 2, 4, 21);
   insert_edge(g, 3, 5, 7);
   insert_edge(g, 3, 6, 5);
   insert_edge(g, 3, 8, 14);
   insert_edge(g, 3, 10, 15);
   insert_edge(g, 4, 5, 24);
   insert_edge(g, 4, 9, 6);
   insert_edge(g, 5, 6, 17);
   insert_edge(g, 5, 7, 8);
   insert_edge(g, 5, 8, 3);
   insert_edge(g, 6, 8, 15);
   insert_edge(g, 6, 10, 12);
   insert_edge(g, 7, 8, 11);
   insert_edge(g, 7, 9, 7);
}

void rec_map(struct Edge *map, int start, int end, int find, double time, int length, int weight, int deep)
{
	int j = 0;
	double t;
	while (j < length)
	{
		t = time;
		if (!(map[j].start == start && map[j].end == end) && map[j].start == find)
		{
			t += (double)1 / weight;
			rec_map(map, map[j].start, map[j].end, map[j].end, t, length, map[j].weight, deep + 1);
		}
		else if (!(map[j].start == start && map[j].end == end) && map[j].end == find)
		{
			t += (double)1 / weight;
			rec_map(map, map[j].start, map[j].end, map[j].start, t, length, map[j].weight, deep + 1);
		}
		j++;
	}
	if (deep != 1)
		printf("===> 사람 %c까지 시간: %f\n", word[find], time);
}

void print_map(struct Edge *map, int length)
{
	int i = 0;
	int j;
	int deep;
	double time;

	while (i <= length)
	{
		printf("사람 %c 출발 ====================\n", word[i]);
		j = 0;
		while (j < length)
		{
			time = 0;
			deep = 0;
			if (map[j].start == i)
				rec_map(map, map[j].start, map[j].end, map[j].end, time, length, map[j].weight, deep + 1);
			if (map[j].end == i)
				rec_map(map, map[j].start, map[j].end, map[j].start, time, length, map[j].weight, deep + 1);
			j++;
		}
		i++;
	}
}

int main(void) {
	clock_t start, stop;
	GraphType* g;
	struct Edge *map;
	int i = 0;
	int len;

	start = clock();
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	g_set(g);
	map = (struct Edge*)malloc(sizeof(struct Edge) * g->n);
	map_init(map, g->n);
	len = kruskal(g, map);
	print_map(map, len);

	stop = clock();
	printf("총 수행시간: %f\n", (double)(stop - start) / CLOCKS_PER_SEC);
	free(g);
	free(map);
	return 0;
}
