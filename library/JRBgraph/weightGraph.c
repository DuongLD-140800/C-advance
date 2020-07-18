//
// Luong Duc Duong
// C-advance
// 
// weightGraph.c
// 
// 

#include "weightGraph.h"

/* ================ create & drop ================== */
Graph createGraph() {
	Graph new;
	new.vertices = make_jrb();
	new.edges = make_jrb();
	return new;
}
void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        if(tree != NULL)
        	jrb_free_tree(tree);
    }
    if (graph.edges != NULL)
    	jrb_free_tree(graph.edges);
    if (graph.vertices != NULL)
    	jrb_free_tree(graph.vertices);
}
/* ================ Vertex function =================== */
void addVertex(Graph graph, int id, char* name) {
	JRB where = jrb_find_int(graph.vertices, id);

	if (where != NULL) return;

	jrb_insert_int(graph.vertices, id, new_jval_s(name));
}

char *getVertexName(Graph graph, int id) {
	JRB where = jrb_find_int(graph.vertices, id);
	if (where == NULL) {
		printf("[!] Cannot find with this id\n");
		return NULL;
	}
	return jval_s(where->val);
}

int checkAddVertex(Graph graph, int v1, int v2) {
	if (jrb_find_int(graph.vertices, v1) == NULL) {
		printf("[!] Vertex %d has not been added to the graph\n", v1);
		return 0;
	}
	if (jrb_find_int(graph.vertices, v2) == NULL) {
		printf("[!] Vertex %d has not been added to the graph\n", v2);
		return 0;
	}
	return 1;
}

int getVertexId(Graph graph, char *name) {
    JRB ptr = NULL;
    jrb_traverse(ptr, graph.vertices) {
        if (strcmp(name, jval_s(ptr->val)) == 0)
            return jval_i(ptr->key);
    }
    return -1;
}

int countVertex(Graph graph) {
	int count = 0;
	JRB ptr = NULL;
	jrb_traverse(ptr, graph.vertices) {
		count++;
	}
	return count;
}
/* ================= Edge funtion ==================== */
void addEdge(Graph graph, int v1, int v2, double weight) {
	if (!checkAddVertex(graph, v1, v2)) return;

	JRB where = jrb_find_int(graph.edges, v1);
	if (where != NULL) {
		jrb_insert_int((JRB)jval_v(where->val), v2, new_jval_d(weight));
	} else {
		JRB nodeV1 = make_jrb();
		jrb_insert_int(nodeV1, v2, new_jval_d(weight));
		jrb_insert_int(graph.edges, v1, new_jval_v((void *)nodeV1));
	}

	/*
	use this code bellow if graph don't have direction
	 */
	
	// where = jrb_find_int(graph.edges, v2);
	// if (where != NULL) {
	// 	jrb_insert_int((JRB)jval_v(where->val), v1, new_jval_d(weight));
	// } else {
	// 	JRB nodeV2 = make_jrb();
	// 	jrb_insert_int(nodeV2, v1, new_jval_d(weight));
	// 	jrb_insert_int(graph.edges, v2, new_jval_v((void *)nodeV2));
	// }
}

void addEdgeNw(Graph graph, int v1, int v2) {
	addEdge(graph, v1, v2, 0);
}
// return INFINITIVE if not has edge
double getEdgeValue(Graph graph, int v1, int v2) {
	if (!checkAddVertex(graph, v1, v2)) return INFINITIVE_VALUE;

	JRB where = jrb_find_int(graph.edges, v1);
	if (where == NULL) return INFINITIVE_VALUE;

	where = jrb_find_int((JRB) jval_v(where->val), v2);
	if (where == NULL)
		return INFINITIVE_VALUE;
	return jval_d(where->val);
}

/* ==================== get adjVertex ===================== */
int indegree(Graph graph, int v, int* output) {
	int counter = 0;

	JRB ptr = NULL;
	jrb_traverse(ptr, graph.edges) {
		if (!jrb_find_int(jval_v(ptr->val), v))
			continue;

		output[counter] = jval_i(ptr->key);
		counter ++;
	}
	return counter;
}

int outdegree(Graph graph, int v, int* output) {
	int counter = 0;
	JRB ptr = NULL;

	JRB where = jrb_find_int(graph.edges, v);
	if (where == NULL) return 0;

	JRB nodeV = (JRB) jval_v(where->val);

	jrb_traverse(ptr, nodeV) {

		output[counter] = jval_i(ptr->key);
		counter ++;
	}
	return counter;
}
// use this function for only direc graph
int getAdjVertes(Graph graph, int v, int* output) {
	int counter = 0;
	JRB ptr = NULL;
	JRB where = jrb_find_int(graph.edges, v);

	if (where != NULL) {
		JRB nodeV = (JRB) jval_v(where->val);

		jrb_traverse(ptr, nodeV) {
			output[counter] = jval_i(ptr->key);
			counter ++;
		}
	}

	jrb_traverse(ptr, graph.edges) {
		if (!jrb_find_int(jval_v(ptr->val), v))
			continue;

		output[counter] = jval_i(ptr->key);
		counter ++;
	}
	return counter;
}
/* ================= Graph search =================== */
void graphBFS(Graph graph, int vStart, int vStop, void (*func) (int)) {
	int visited[MAX_V] = {0};

	Queue verQue = initQueue();
	enQueue(verQue, vStart);

	// array of adjacent vertex
	int adjVer[MAX_V] = {0};
	// number of adjacent vertex
	int countVer = 0;
	// vertex now
	int vertexNow = -1;

	while (!isEmptyQueue(verQue)) {
		vertexNow = deQueue(verQue);

		if ( visited[vertexNow] )
			continue;
		// if not visited v
		func(vertexNow);
		visited[vertexNow] = 1;
		if (vertexNow == vStop) break;
		// get adjacent vertex of v
		countVer = outdegree(graph, vertexNow, adjVer);
		// add adjacent vertex of v to queue
		for (int i = 0; i < countVer; ++i) {
			if ( !visited[adjVer[i]] )
				enQueue(verQue, adjVer[i]);
		}
	}
	freeQueue(verQue);
}

void graphDFS(Graph graph, int vStart, int vStop, void (*func) (int)) {
	// set all visited = false
	int visited[MAX_V] = {0};
	
	Stack verSta = initStack();
	pushStack(verSta, vStart);

	// array of adjacent vertex
	int adjVer[MAX_V] = {0};
	// number of adjacent vertex
	int countVer = 0;
	// vertex now
	int vertexNow = -1;

	while (!isEmptyStack(verSta)) {
		vertexNow = popStack(verSta);

		if ( visited[vertexNow] )
			continue;
		// if not visited v
		func(vertexNow);
		visited[vertexNow] = 1;
		if (vertexNow == vStop) break;
		// get adjacent vertex of v
		countVer = outdegree(graph, vertexNow, adjVer);
		// add adjacent vertex of v to stack
		for (int i = 0; i < countVer; ++i) {
			if ( !visited[adjVer[i]] )
				pushStack(verSta, adjVer[i]);
		}
	}
	freeStack(verSta);
}

/* ================= DAG check =================== */
int DAG(Graph graph)
{
   	int visited[MAX_V] = {0};
   	int output[MAX_V] = {0};
   	int v = 0, vNow = 0;
   	JRB vertex;
   
   	jrb_traverse(vertex, graph.vertices) {

   		memset(visited, 0, sizeof(visited));
       	Stack top = initStack();

       	int start = jval_i(vertex->key);     
       	pushStack(top, start);
    
   	    while (!isEmptyStack(top)) {

        	vNow = popStack(top);

          	if (!visited[vNow]) {
              	visited[vNow] = 1;
              	int totalOut = outdegree(graph, vNow, output);
              	for (int i = 0; i < totalOut; i++) {
                  	v = output[i];
                  	if ( v == start ) // cycle detected 
                    	return 0;
                  	if (!visited[v])    
                    	pushStack(top, v);
              	}
          	}           
       	}
       	freeStack(top);
   	}
   	return 1; // no cycle    
}
/* ============ convert to matrix =============== */
int **convertGraph(Graph graph) {
	int vertex = countVertex(graph);
	int **matrixGraph = NULL;
	matrixGraph = (int **) calloc(vertex, sizeof(int *));
	if (matrixGraph == NULL) {
		printf("[!] Malloc failed at <**matrixGraph>\n");
		exit(1);
	}

	for (int i = 0; i < vertex; i++) {
		*(matrixGraph + i) = (int *) calloc(vertex, sizeof(int));
		if (*(matrixGraph + i) == NULL) {
			printf("[!] Malloc failed at <*(matrixGraph + %d)>\n", i);
			exit(1);
		}
	}
	int value = 0;
	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			// if id start from 0 use this code
			// value = getEdgeValue(graph, i, j);

			// if id start from 1 use this code
			value = getEdgeValue(graph, i + 1, j + 1);
			if (value == INFINITIVE_VALUE)
				matrixGraph[i][j] = 0;
			else 
				matrixGraph[i][j] = value;
		}
	}
	return matrixGraph;
}
void printMatrix(int **matrix, int vertex) {
	for (int i = 0; i <= vertex; i++) {
		if ( i == 0) printf (" 0 ");
		else printf ("%2d ", i);
		for (int j = 0; j < vertex; j++) {
			if (i == 0) 
				printf("%2d ", j + 1);
			else 
				printf("%2d ", matrix[i-1][j]);
		}
		printf("\n");
	}
}
void freeMatrix(int **matrix, int vertex) {
	for (int i = 0; i < vertex; i++) {
		if (*(matrix + i) != NULL)
			free(*(matrix + i));
	}
	if (matrix != NULL)
		free(matrix);
}
/* ================= Topology sort ====================== */
int sortTopology(Graph  graph, int output[]) {
	JRB ptr = NULL;
	Queue front = initQueue();
	int arr[MAX_V] = {0};
	int inDgr[MAX_V] = {0};
	int counter = 0;

	jrb_traverse(ptr, graph.vertices) {
		int v = jval_i(ptr->key);
		inDgr[v] = indegree(graph, v, arr);
		if (inDgr[v] == 0) enQueue(front, v);
	}

	while (!isEmptyQueue(front)) {
		int vertexNow = deQueue(front);
		output[counter] = vertexNow;
		inDgr[vertexNow] = -1;
		counter++;

		int totalOutDg = outdegree(graph, vertexNow, arr);

		for (int i = 0; i < totalOutDg; i++){
			inDgr[arr[i]]--;
			if (inDgr[arr[i]] == 0) {
				enQueue(front, arr[i]);
			}
		}
	}
	freeQueue(front);
	return counter;
}
/* ==================== shortest path ========================= */
void relaxWeight(Graph g, int u, int v, int d[], int parent[]) {
	if (d[v] > d[u] + getEdgeValue(g, u, v)) {
		d[v] = d[u] + getEdgeValue(g, u, v);
		parent[v] = u;
	}
}

void relaxStep(Graph g, int u, int v, int d[], int parent[]) {
	if (d[v] > d[u] + 1) {
		d[v] = d[u] + 1;
		parent[v] = u;
	}
}

static int getMinD(int d[], int visited[]) {
	int min = INFINITIVE_VALUE;
	int posMin = -1;
	for (int i = 0; i < MAX_V; i++) {
		if ((visited[i] == 0) && (d[i] < min)) {
			posMin = i;
			min = d[i];
		}
	}
	return posMin;
}
/**
 * use function <relaxWeight> if need weight min
 * use function <relaxStep> if need step min
 */
double shortestPath(Graph g, int s, int t, int *path, int *length,
					void (*relaxFunc)(Graph, int, int, int *, int *)) 
{
	*length = 0;
	int parent[MAX_V];
	int d[MAX_V];
	int visited[MAX_V];

	JRB ptr;
	int vNow = -1;
	int size = 0;
	int output[MAX_V] = {0};
	int total;
	int check = 0;

	for (int i = 0; i < MAX_V; i++) {
		visited[i] = -1;
	}

	jrb_traverse(ptr, g.vertices) {
		vNow = jval_i(ptr->key);
		parent[vNow] = -1;
		visited[vNow] = 0;
		if (vNow == s) d[vNow] = 0;
		else d[vNow] = INFINITIVE_VALUE;
		size++;
	}
	while (size != 0) {
		vNow = getMinD(d, visited);
		visited[vNow] = 1;

		if (vNow == t) {
			check = 1;
			break;
		}

		total = outdegree(g, vNow, output);
		for (int i = 0; i < total; i++) {
			relaxFunc(g, vNow, output[i], d, parent);
		}
		size--;
	}
	// if not found the way
	if (t == -1 || !check) {
		*path = 0;
		*length = 0;
		return 0;
	}
	for (int i = 0; i < MAX_V; i++) {
		path[i] = vNow;
		vNow = parent[vNow];
		if (vNow == 0) break;
		(*length)++;
	}
	int swap = 0;
	for (int i = 0; i < (*length + 1) / 2; i++) {
		swap = path[i];
		path[i] = path[*length - 1 - i];
		path[*length - 1 - i] = swap;
	}
	(*length) --;
	return d[t];
}
/* =================== Prim althro ================== */
static int checkExistArr(int x, int arr[], int sizeArr) {
	for (int i = 0; i < sizeArr; i++) {
		if (arr[i] == x) return 1;
	}
	return 0;
}
static int getMinEdgeOfVertex(Graph graph, int v, int *vEnd, int visited[], int sizeVisited) {
	int output[MAX_V] = {0};
	int totalOut = outdegree(graph, v, output);
	int min = INFINITIVE_VALUE;
	for (int i = 0; i < totalOut; i++) {
		if (checkExistArr(output[i], visited, sizeVisited))
			continue;
		if (min > getEdgeValue(graph, v, output[i])) {
			min = getEdgeValue(graph, v, output[i]);
			*vEnd = output[i];
		}
	}
	return min;
}
// use prim algorithm
void minSpanningTree(Graph graph) {
	int totalVertex = countVertex(graph);
	int visited[MAX_V] = {0};
	int vNow = 1; // start with vertex 1

	printf("Prim Algorithm resuilt:\n\n");

	for (int i = 0; i < totalVertex - 1; ++i) {
		visited[i] = vNow;
		int min = INFINITIVE_VALUE;
		int vStart = -1;
		int vEnd = -1;
		for (int j = 0; j <= i; j++) {
			int minV = getMinEdgeOfVertex(graph, visited[j], &vEnd, visited, i+1);
			if (min > minV) {
				min = minV;
				vNow = vEnd;
				vStart = visited[j];
			}
		}
		printf(" %d.Edge: %d->%d - Weight: %d\n", i+1, vStart, vNow, min);
	}
}
//