#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stats.h"
#define Maxsize 100
#define INF 32765
int p[Maxsize];//表头
int InDegree[Maxsize];//入度
int OutDegree[Maxsize];//出度

int numberOfEdges(char name[]) {
	FILE *f;
	f = fopen(name, "r");
	int u, v, w;
	int row = 0;
	while (fscanf(f, "%d%d%d", &u, &v, &w) != EOF) {
		row++;
	}
	fclose(f);
	return row;
}

int numberOfVertices(char name[]) {
	int n = 0;
	int u, v, w;
	FILE *f;
	f = fopen(name, "r");
	while (fscanf(f, "%d%d%d", &u, &v, &w) != EOF) {
		InDegree[v]++;
		OutDegree[u]++;
	}
	for (int i = 0; i < Maxsize; i++) {
		if (InDegree[i] || OutDegree[i]) {
			n++;
		}
	}
	fclose(f);
	return n;
}

double freemanNetworkCentrality(char name[]) {
	int n = numberOfVertices(name);
	int max = InDegree[0];
	for (int i = 0; i < n; i++) {
		if (InDegree[i]>max) {
			max = InDegree[i];
		}
	}
	double sum = 0;
	for (int i = 0; i<n; i++) {
		sum += (max - InDegree[i]);
	}
	return sum / ((n - 1)*(n - 2)) / 2;

}

double closenessCentrality(char name[]) {
	int n = numberOfVertices(name);
	double MaxClose = 0;
	double min = INF;
	int map[Maxsize][Maxsize];
	double close[Maxsize] = { 0 };
	FILE *f;
	f = fopen(name, "r");
	int u, v, w;
	for (int i = 0; i<n; i++)
		for (int j = 0; j < n; j++) {
			if (i == j) map[i][j] = 0;
			else map[i][j] = INF;
		}
	while (fscanf(f, "%d%d%d", &u, &v, &w) != EOF) {
		map[u][v] = w;
	}
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (map[i][j] > map[i][k] + map[k][j])
					map[i][j] = map[i][k] + map[k][j];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			close[i] += map[i][j];
		}
		if (min > close[i])
			min = close[i];
	}
	MaxClose = (n - 1) / min;
	return MaxClose;
}

int main(void)
{
	char name[] = "./test.txt";
	printf("e=%d\n", numberOfEdges(name));
	printf("n=%d\n", numberOfVertices(name));
	printf("freeman=%lf\n", freemanNetworkCentrality(name));
	printf("closeness=%lf\n", closenessCentrality(name));
	return 0;
}
