#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "queue.c"
#include "queue.h"
#include "priority_queue.c"
#include "priority_queue.h"

int h[N], vis[N];
priority_queue pq;
int path_DFS[100];

//DFS
void print_DFS();
int dfs(int u, int v, int count, int length, char Name[]);


//Dijkstra
void Dijkstra(int v, int des);
void Dispath(int dist[], int path[], int S[], int v, int des);



//BFS
AdjGraph* CreateAdj(int n,int e, char Name[]);
int BFS2(AdjGraph *G, int u, int v, int path[]);
int BFS(int u, int v,char Name[], int path[]);

//spfa
int SPFA2(int matrix[][100], int vertex_num, int source, int path[], int dist[]);
void Print(int des, int source, int path[], int dist[]);
int SPFA(int u, int v, char name[], int path[]);

//A*
void add(int u, int v, int w);
void Astar(int src, int des);
void spfa_Astar(int s, int des);

//最短路径
int* shortestPath(int u, int v, char algorithm[], char name[]);
