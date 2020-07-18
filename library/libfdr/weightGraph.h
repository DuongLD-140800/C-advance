// Luong Duc Duong
// 
// C-advance
// 
// weightGraph.h
// 
/* **************************** */


#ifndef _WEIGHT_GRAPH_
#define _WEIGHT_GRAPH_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jrb.h"
#include "queue.h"
#include "stack.h"

#define MAX_V 10000
#define INFINITIVE_VALUE 10000000

typedef struct {
	JRB edges;
	JRB vertices;
} Graph;


//
/* =========== create & drop =============== */
Graph createGraph();
void dropGraph(Graph graph);
/* =========== vertex function ============= */
int checkAddVertex(Graph graph, int v1, int v2);
void addVertex(Graph graph, int id, char* name);
int getVertexId(Graph graph, char *name);
char *getVertexName(Graph graph, int id);
int countVertex(Graph graph);
/* ============ edge function ============= */
void addEdge(Graph graph, int v1, int v2, double weight);
void addEdgeNw(Graph graph, int v1, int v2);
double getEdgeValue(Graph graph, int v1, int v2);
/* ============ adj vertex function ==============*/
int indegree(Graph graph, int v, int* output);
int outdegree(Graph graph, int v, int* output);
int getAdjVertes(Graph graph, int v, int* output);
/* ================= Graph search =================== */
void graphBFS(Graph graph, int vStart, int vStop, void (*func) (int));
void graphDFS(Graph graph, int vStart, int vStop, void (*func) (int));
/* ================= DAG check =================== */
int DAG(Graph graph);
/* ============ convert to matrix =============== */
int **convertGraph(Graph graph);
void printMatrix(int **matrix, int vertex);
void freeMatrix(int **matrix, int vertex);
/* ============ topology sort =============== */
int sortTopology(Graph  graph, int output[]);
/* ============ shortest path =============== */
void relaxWeight(Graph g, int u, int v, int d[], int parent[]);
void relaxStep(Graph g, int u, int v, int d[], int parent[]);
double shortestPath(Graph g, int s, int t, int *path, int *length,
					void (*relaxFunc)(Graph, int, int, int *, int *));
/* =================== Prim althro ================== */
void minSpanningTree(Graph graph);
/* =========================================== */
//


#endif



