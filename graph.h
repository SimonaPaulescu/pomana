#ifndef GRAPH_H
#define GRAPH_H		1

typedef struct linkedlist { // linked list of ints (for use in Node)
	int index;
	struct linkedlist *next;
} List;

typedef struct { // a Node of a Graph
	char *name;
	List *outlist; // adjacency list
	int outdegree; // length of outlist
	//double pagerank_score; //not needed for this exercise  int indegree;
	int indegree;
	int index;
	int state;
	int reachableNodes;
} Node;

typedef struct {
	// your code goes here
	Node *table;
	int MaxSize;
} Graph;

// Use to check result of strdup, malloc etc.
extern void check (void *memory, char *message);
extern void initialize_graph (Graph *mygraph, int MaxSize);
extern void insert_graph_node (Graph *mygraph, int n, char *name);
extern void insert_graph_link (Graph *mygraph, int source, int target);
extern int read_graph (Graph *mygraph, char *filename);
extern void print_graph (Graph *mygraph);
extern void dijkstra(Graph *mygraph, int start);
extern void set_states_unvisited(Graph *mygraph);
extern int checkList(int target, Node node);
extern Node findMax(List *list, Graph *graph);
extern void heuristicSearch(Graph *graph, int target);

#endif
