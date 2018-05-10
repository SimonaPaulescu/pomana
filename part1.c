#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc,char *argv[])
{
	Graph mygraph;
	int rc, i;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <path-to-input-file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	rc = read_graph(&mygraph,argv[1]);
	if (rc < 0)
		exit(EXIT_FAILURE);

	for (i = 1; i <= mygraph.MaxSize; i++) {
		 heuristicSearch(&mygraph, i);
		// dijkstra(&mygraph, 2);
	}
	//heuristicSearch(&mygraph, 23);
	//print_graph(&mygraph);
	//dijkstra(&mygraph, 1);
	return(0);
}
