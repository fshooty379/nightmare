#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#include "stats.c"
#include "queue.c"
#include "queue.h"
#include "priority_queue.c"
#include "priority_queue.h"
#include "search.h"
#define Maxsize 100
#define INF 32676
#define N 55
//DFS
void print_DFS(int mincount)
{
	for (int i = 0; i <= mincount; i++)
	{
		printf("%d", path_DFS[i]);
		if (i < mincount)
			printf("->");
	}
}

int dfs(int u, int v, int count, int length, char Name[])
{
	MatGraph g = CreateMat(n, e, Name[]);
	visited[u] = 1;
	path1[count] = u;
	int mincount;
	if (length >= minl)
		return;
	if (u == v && length < minl)
	{
		minl = length;
		mincount = count;
		for (int i = 0; i < minl; i++)
			path_DFS[i] = path1[i];
		return;
	}
	for (int i = 0; i < g.n; i++)
	{
		if (g.edges[u][i] != INF && u != i && visited[i] == 0)
		{
			dfs(i, v, count + 1, length + g.edges[u][i]);
			visited[i] = 0;
		}
	}
	return mincount;
}
//BFS
AdjGraph* CreateAdj(int n,int e, char Name[]) {
	int a[Maxsize][Maxsize];
	for(int i=0;i<n;i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j) a[i][j] = 0;
			else a[i][j] = INF;
		}
	FILE *f = fopen(Name, "r");
	int u, v, w;
	while (fscanf(f,"%d%d%d",&u, &v, &w) != EOF)
	{
		a[u][v] = w;
	}
	fclose(f);
	int i, j;
	ArcNode *p;
	AdjGraph *G;
	G = (AdjGraph*)malloc(sizeof(AdjGraph));
	for (i = 0; i < n; i++)
		G->adjlist[i].firstarc = NULL;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if (a[i][j] != 0 && a[i][j] != INF)
			{
				p = (ArcNode*)malloc(sizeof(ArcNode));
				p->adjvex = j;
				p->weight = a[i][j];
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
	G->n = n;
	G->e = e;
	return G;
}

int BFS2(AdjGraph *G, int u, int v, int path[]) {
	int vis[Maxsize] = { 0 };
	for (int i = 0; i < G->n; i++)
		vis[i] = 0;
	struct
	{
		int vno;
		int level;
		int parent;
	}qu[Maxsize];
	int front = -1, rear = -1, k, lev, i, j;
	ArcNode *p;
	vis[u] = 1;
	rear++;
	qu[rear].vno = u;
	qu[rear].level = 0;
	qu[rear].parent = -1;
	while (front < rear)
	{
		front++;
		k = qu[front].vno;
		lev = qu[front].level;
		if (k == v)
		{
			i = 0;
			j = front;
			while (j != -1)
			{
				path[lev - i] = qu[j].vno;
				j = qu[j].parent;
				i++;
			}
			return lev;
		}
		p = G->adjlist[k].firstarc;
		while (p != NULL)
		{
			if (vis[p->adjvex] == 0)
			{
				vis[p->adjvex] = 1;
				rear++;
				qu[rear].vno = p->adjvex;
				qu[rear].level = lev + 1;
				qu[rear].parent = front;
			}
			p = p->nextarc;
		}
	}
	return -1;
}

int BFS(int u, int v, char Name[], int path[]) {
	int n = numberOfEdges(Name);
	int e = numberOfVertices(Name);
	AdjGraph *G = CreateAdj(n, e, Name);
	int len = BFS2(G, u, v, path);
    printf("%d", path[0]);
    for (int i = 1; i < len; i++)
		printf("->%d", path[i]);
	return len;
}


//spfa
int SPFA2(int matrix[100][100], int vertex_num, int source, int path[100], int dist[100])
{
	int visited[100];
	int enqueue_num[100];
	int rear, front, qu[100];
	rear = front = -1;
	for (int i = 0; i < vertex_num; i++)
		visited[i] = 0;
	for (int i = 0; i < vertex_num; i++)
		enqueue_num[i] = 0;
	for (int i = 0; i < vertex_num; i++)
	{
		dist[i] = INF;
		path[i] = source;
	}
	rear++;
	qu[rear] = source;
	dist[source] = 0;
	visited[source] = 1;
	enqueue_num[source]++;
	while (rear != front)
	{
		front++;
		int u = qu[front];
		visited[u] = 0;
		for (int v = 0; v < vertex_num; v++)
		{
			if (matrix[u][v] != INF)  //u与v直接邻接
			{
				if (dist[u] + matrix[u][v] < dist[v])
				{
					dist[v] = dist[u] + matrix[u][v];
					path[v] = u;
					if (!visited[v])
					{
						rear++;
						qu[rear] = v;
						enqueue_num[v]++;
						if (enqueue_num[v] >= vertex_num)
							return 0;
						visited[v] = 1;
					}
				}
			}
		}
	}
	return 1;
}
void Print(int des, int source, int path[100], int dist[100])
{
	int top = -1;
	int st[100];
		if (des != source)
		{
			int p = des;
			printf("%d到%d最短路径为:", source, p);
			while (source != p)  //路径顺序是逆向的，所以先保存到栈
			{
				top++;
				st[top] = p;
				p = path[p];
			}
			printf("%d", source);
			while (top != -1)  //依次从栈中取出的才是正序路径
			{
				printf("->%d", st[top]);
				top--;
			}
		}
	
}
int SPFA(int u, int v, char name[], int path[])
{
	int dist[100];
	int source, edge_num, vertex_num, des;
	source = u, des = v;
	vertex_num = numberOfVertices(name);
	edge_num = numberOfEdges(name);
	int matrix[100][100];
	vertex_num = numberOfVertices(name);
    edge_num = numberOfEdges(name);
	for (int i = 0; i < vertex_num; i++)
		for (int j = 0; j < vertex_num; j++)
			matrix[i][j] = INF;  //初始化matrix数组
	FILE *f = fopen(name, "r");
	int a, b, c;
	while (fscanf(f, "%d%d%d", &a, &b, &c) != EOF)
	{
		matrix[a][b] = c;
	}
	fclose(f);
	if (SPFA2(matrix, vertex_num, source, path, dist))
		Print(des, source, path, dist);
	else
		printf("无最短路径!\n");
    return dist[des];
}

//Dijkstra
void Dispath(int dist[], int path[], int S[], int v, int des)
//输出从顶点v出发的所有最短路径
{
	int i, j, k;
	int apath[MAXV], d;					//存放一条最短路径(逆向)及其顶点个数
	if (S[des] == 1 && des != v)
		d = 0; apath[d] = des;			//添加路径上的终点
	k = path[des];
	if (k == -1)				//没有路径的情况
		printf("无路径\n");
	else
	{

		while (k != v)
		{
			d++; apath[d] = k;
			k = path[k];
		}
		d++; apath[d] = v;		//添加路径上的起点
		printf("%d", apath[d]);	//先输出起点
		for (j = d - 1; j >= 0; j--)	//再输出其他顶点
			printf("->%d", apath[j]);
		printf("\n");
	}

}

void Dijkstra(int v, int des)	//Dijkstra算法
{
	int dist[MAXV], path[MAXV];
	int S[MAXV];				//S[i]=1表示顶点i在S中, S[i]=0表示顶点i在U中
	int Mindis, i, j, u;
	for (i = 0; i < g.n; i++)
	{
		dist[i] = g.edges[v][i];	//距离初始化
		S[i] = 0;					//S[]置空
		if (g.edges[v][i] < INF)	//路径初始化
			path[i] = v;			//顶点v到顶点i有边时，置顶点i的前一个顶点为v
		else
			path[i] = -1;			//顶点v到顶点i没边时，置顶点i的前一个顶点为-1
	}
	S[v] = 1; path[v] = 0;			//源点编号v放入S中
	for (i = 0; i < g.n - 1; i++)			//循环直到所有顶点的最短路径都求出
	{
		Mindis = INF;				//Mindis置最大长度初值
		for (j = 0; j < g.n; j++)		//选取不在S中（即U中）且具有最小最短路径长度的顶点u
			if (S[j] == 0 && dist[j] < Mindis)
			{
				u = j;
				Mindis = dist[j];
			}
		S[u] = 1;					//顶点u加入S中
		for (j = 0; j < g.n; j++)		//修改不在S中（即U中）的顶点的最短路径
			if (S[j] == 0)
				if (g.edges[u][j] < INF && dist[u] + g.edges[u][j] < dist[j])
				{
					dist[j] = dist[u] + g.edges[u][j];
					path[j] = u;
				}
	}
	Dispath(dist, path, S, v, des);	//输出最短路径
}

//A*
void add(int u, int v, int w) {
	e[eid].v = v;
	e[eid].w = w;
	e[eid].next = p[u];
	p[u] = eid++;
	ex[exid].v = u;
	ex[exid].w = w;
	ex[exid].next = px[v];
	px[v] = exid++;
}

void Astar(int src, int des) { //src -> des
	queue q; // 路径
	queue_init(&q);
	queue_push(&q, src);
	node tmp = { src, 0, h[src], q };
	pq_init(&pq);
	pq_push(&pq, tmp);
	while (pq_size(&pq)) {
		tmp = pq_pop(&pq);
		if (tmp.v == des) {
			queue_print(&tmp.path);
			return;
		}
		for (int i = p[tmp.v]; ~i; i = e[i].next) {
			if (ok(&tmp.path, e[i].v)) {
				continue;
			}
			node to = tmp;
			to.v = e[i].v;
			to.g += e[i].w; //to.g:s->u  e[i].w:u->v
			to.h = h[e[i].v];
			queue_push(&to.path, e[i].v);
			pq_push(&pq, to);
		}
	}
	return;
}

void spfa_Astar(int s, int des) 
{
	memset(h, 0x3f, sizeof h);
	h[s] = 0;
	memset(vis, 0, sizeof vis);
	vis[s] = 1;
	Queue q;
	Queue_init(&q);
	Queue_push(&q, s);
	while (Queue_size(&q)) {
		int u = Queue_pop(&q);
		vis[u] = 0;
		for (int i = px[u]; ~i; i = ex[i].next) {
			int v = ex[i].v;
			if (h[v] > h[u] + ex[i].w) {
				h[v] = h[u] + ex[i].w;
				if (!vis[v]) {
					vis[v] = 1;
					Queue_push(&q, v);
				}
			}
		}
	}
	Astar(s, des);
}
//最短路径
int* shortestPath(int u, int v, char algorithm[], char name[])
{
	if (strcmp(algorithm, "DFS"))
		print_DFS(dfs(u, v, 0, 0, name));
	if (strcmp(algorithm, "BFS")
	{	
		int path[100];
		BFS(u, v, name,path );
	}
	if (strcmp(algorithm, "Dijkstra")
	{
		Dijkstra(u, v);
	}
	if (strcmp(algorithm, "SPFA")
	{
		int path[100];
		char name="test.txt";
		SPFA(u, v,name,path);
	}
	if (strcmp(algorithm, "Astar")
	{
		Astar(u, v);
	}
}
