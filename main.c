#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stats.h"
#include "search.h"

int main(int argc, char *argv[]) {
	if (argv[1] == "-h" || argv[1] == "--help") {
		printf("======================帮助菜单========================\n");
		printf("<1> 输入-g/--graph 文件地址 -s/--stats 参数 以显示统计信息\n");
		printf("具体参数有:\n");
		printf("edges\n");
		printf("vertices\n");
		printf("freeman\n");
		printf("closeness\n");
		printf("<2> 输入-g/--graph 文件地址 -sp/--shortestpath 参数 -u 源点 -v 终点 以显示最短路径\n");
		printf("具体参数有:\n");
		printf("DFS\n");
		printf("BFS\n");
		printf("Dijkstra\n");
		printf("spfa\n");
		printf("A*\n");
		printf("请输入指令:\n");
	}
	if (argv[1] == "-g" || argv[1] == "--graph") {
		char name[100];
		strcpy(name, argv[2]);
		if (argv[3] == "-s" || argv[3] == "--stats") {
			char STATS_PARAMS[20];
			strcpy(STATS_PARAMS, argv[4]);
			if (strcmp(STATS_PARAMS, "edges") == 0) {
				printf("%d\n", numberOfEdges(name));
			}
			if (strcmp(STATS_PARAMS, "vertices") == 0) {
				printf("%d\n", numberOfVertices(name));
			}
			if (strcmp(STATS_PARAMS, "freeman") == 0) {
				printf("%lf\n", freemanNetworkCentrality(name));
			}
			if (strcmp(STATS_PARAMS, "closeness") == 0) {
				printf("%lf\n", closenessCentrality(name));
			}
		} else if (argv[3] == "-sp" || argv[3] == "--shortestpath") {
			char SEARCH_PARAMS[20];
			strcpy(SEARCH_PARAMS, argv[4]);
            int path[Maxsize];
            if (argv[5] == "-u" && argv[7] == "-v") {
                int u = argv[6][0] - '0';
                int v = argv[8][0] - '0';
            }
            path = shortestPath(u, v, SEARCH_PARAMS, name);

		}
	}
	return 0;
}
