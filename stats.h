//stats.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ANode {
	int adjvex;
	struct ANode *nextarc;
	int weight;
};
typedef struct ANode ArcNode;
struct Vnode {
	ArcNode *firstarc;
};
typedef struct Vnode VNode;
struct ADJGraph{
	VNode adjlist[100];
	int n, e;
};
typedef struct ADJGraph AdjGraph;

int numberOfEdges(char name[]);
int numberOfVertices(char name[]);
double freemanNetworkCentrality(char name[]);
double betweennessCentrality(char name[]);
double closenessCentrality(char name[]);
double eigenvectorCentrality(char name[]);
