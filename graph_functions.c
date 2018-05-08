#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

void set_states_unvisited(Graph *mygraph) {
	int i;
	for(i = 1; i<= mygraph->MaxSize; i++) {
		//printf("Set state  from %d to 0\n", mygraph->table[i].state);
		mygraph->table[i].state = 0;
	}
}

void unset_reachable_nodes(Graph *mygraph) {
	int i;
	for(i = 1; i<= mygraph->MaxSize; i++) {
		mygraph->table[i].reachableNodes = 0;
	}
}

void initialize_graph(Graph *mygraph, int MaxSize)
{
	mygraph->table = calloc(MaxSize, sizeof(Node));
	if (mygraph->table == NULL) {
		fprintf(stderr, "Problem allocating memory for priority queue. Reduce SIZE.\n");
		exit(EXIT_FAILURE);
	}
	mygraph->MaxSize = MaxSize;
	printf("Size is %d\n", mygraph->MaxSize);
}

void insert_graph_node(Graph *mygraph, int n, char *name)
{
	Node myNode;

	myNode.name = malloc(32);
	myNode.name = strdup(name);
	//set the outdegree to be 0 initially
	myNode.outdegree = 0;
	myNode.indegree = 0;
	myNode.index = n;
	myNode.outlist = NULL;
	myNode.state = 0;
	myNode.reachableNodes = 0;
	mygraph->table[n] = myNode;
	//printf("Node name is %s and position is %d\n", mygraph->table[n].name, n);
}

void insertInList(List *head, int target)
{
	List *workingList = (List *) malloc(sizeof(List));
	if (workingList == NULL){
		fprintf(stderr, "Can't allocate memory for\n");
		exit(EXIT_FAILURE);
	}
	workingList->index = target;
	workingList->next = NULL;

	if(head->next == NULL){
		head->next = workingList;
		//printf("No element, added %d\n", head->next->index);
	}
	else {
		List *current = head;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = workingList;
		//printf("There are more elements and i added %d\n", current->next->index);
	}
}

void insert_graph_link(Graph *mygraph, int source, int target)
{
	//printf("name is %s \n", mygraph->table[source].name);

	// If the list is null we add the first element.
	if(mygraph->table[source].outlist == NULL){
		mygraph->table[source].outlist = (List*)malloc(sizeof(List));
		mygraph->table[source].outlist->index = target;
		mygraph->table[source].outlist->next = NULL;
	}
	// Else we use the insert function.
	else{
		insertInList(mygraph->table[source].outlist, target);
		mygraph->table[source].outdegree++;
		mygraph->table[target].indegree++;
		List *checkList = (List *) malloc(sizeof(List));
		checkList = mygraph->table[source].outlist;
		//printf("Targets are\n");
		while (checkList != NULL){
			//printf("%d\n", checkList->index);
			checkList = checkList->next;
		}
	}
}

// Use to check result of strdup, malloc etc.
void check(void *memory, char *message)
{
	if (memory == NULL) {
		fprintf(stderr, "Can't allocate memory for %s\n", message);
		exit(EXIT_FAILURE);
	}
}

int read_graph(Graph *mygraph, char *filename)
	/*
	 * Reads in graph from FILE *filename which is of .gx format.
	 * Stores it as Graph in *mygraph.
	 * Returns an error if file does not start with MAX command,
	 * or if any subsequent line is not a NODE or EDGE command.
	 * Does not check that node numbers do not exceed the maximum number
	 * Defined by the MAX command.
	 * 8/2/2010 - JLS
	 */
{
	FILE *fp;
	char command[80], name[80];
	int i, s, t;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "cannot open file %s\n", filename);
		return -1;
	}

	printf("Reading graph from %s\n", filename);
	fscanf(fp,"%s", command);
	if (strcmp(command, "MAX") != 0) {
		fprintf(stderr, "Error in graphics file format\n");
		return -1;
	}

	fscanf(fp, "%d", &i);
	initialize_graph(mygraph, i+1); // +1 so nodes can be numbered 1..MAX
	while (fscanf(fp, "%s", command) != EOF) {
		if (strcmp(command, "NODE")==0) {
			fscanf(fp, "%d %s", &i, name);
			insert_graph_node(mygraph, i, name);
		}
		else {
			if (strcmp(command, "EDGE") !=0)
				return -1;
			fscanf(fp, "%d %d", &s, &t);
			insert_graph_link(mygraph, s, t);
		}
	}
	return 0;
}

void print_graph(Graph *mygraph)
	/*
	 * Prints out Graph *mygraph to the stdout in .gx format - JLS
	 */
{
	int i;
	List *current;

	printf ("MAX %d\n", mygraph->MaxSize);
	for (i = 0; i < mygraph->MaxSize; i++)
		if (mygraph->table[i].name != NULL) {
			printf("NODE %d %s\n", i, mygraph->table[i].name);
			current = mygraph->table[i].outlist;
			while (current != NULL) {
				printf("EDGE %d %d\n", i, current->index);
				current = current->next;
			}
		}
}
