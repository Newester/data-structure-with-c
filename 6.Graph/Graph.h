#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "../Common.h"

#define VERTEXS_NUM 100

typedef struct {
    DataType vertexs[VERTEXS_NUM];
    DataType arcs[VERTEXS_NUM][VERTEXS_NUM];
    int vertexs_num;
    int arcs_nums;    
} Digraph;

void Digraph_Init(Digraph* g);
void Digraph_Destroy(Digraph* g);
void Digraph_BFS(Digraph* g);
void Digraph_DFS(Digraph* g);
void Digraph_Dijkstra(Digraph* g, int source);
void Digraph_Floyd(Digraph* g);
void Digraph_TopologicalSort(Digraph* g);
void Digraph_Prim(Digraph* g);
void Digraph_Kruskal(Digraph* g);

#endif // !__GRAPH_H__