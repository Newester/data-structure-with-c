#include <limits.h>
#include "../4.Queue/Queue.h"
#include "Graph.h"


static int visited[VERTEXS_NUM];

void Digraph_Init(Digraph* g) {
    for(int i = 0; i < VERTEXS_NUM; i++) {
        for(int j = 0; j < VERTEXS_NUM; j++) {
            g->arcs[i][j] = INT_MAX;
        }
    }
}
void Digraph_Destroy(Digraph* g) {
    if(NULL != g) {
        free(g);
    }
}
void Digraph_BFS(Digraph* g) {
    Queue* q = Queue_New();
    for(int i = 0; i < VERTEXS_NUM; i++) {
        visited[i] = 0;
    }
    Queue_EnQueue(q, 0);
    while(TRUE != Queue_IsEmpty(q)) {
        int cur;
        Queue_DeQueue(q, &cur);
        for (int i = 0; i < VERTEXS_NUM; ++i) {
            if (g->arcs[cur][i] < INT_MAX && 0 == visited[i]) {
                visited[i] = 1;
                printf("%d\n", g->vertexs[i]);
                Queue_EnQueue(&q, i);
            }
        }
    }
}
void Digraph_DFS(Digraph* g) {
    for(int i = 0; i < VERTEXS_NUM; i++) {
        visited[i] = 0;
    }
    for(int i = 0; i < VERTEXS_NUM; i++) {
        if(0 == visited[i]) {
            Graph_DFS(g, i);
        }
    }
}
static void Graph_DFS(Digraph* g, int i) {
    printf("visit %d\n", g->vertexs[i]);
    for(int j = 0; j <  VERTEXS_NUM;j++) {
        if(g->arcs[i][j] < INT_MAX && 0 == visited[j]) {
            Graph_DFS(g, i);
        }
    }
}
void Digraph_Dijkstra(Digraph* g, int source) {
    int src_distance[VERTEXS_NUM];
}
void Digraph_Floyd(Digraph* g) {}
void Digraph_TopologicalSort(Digraph* g) {}
void Digraph_Prim(Digraph* g) {}
void Digraph_Kruskal(Digraph* g) {}