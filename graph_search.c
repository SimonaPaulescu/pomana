#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int full(int *array, int size) {

	int i, count = 0;

	//printf("Elements are \n");
	for (i = 1; i < size; i++) {
		//printf("%d\n", array[i]);
		if (array[i] == 0) {
			return 0;
		}
	}

	return 1;
}

void dijkstra(Graph *graph, int start) {

	int size = graph->MaxSize;
	int *distance, distanceVal = 1, current = start, minIndex, minVal, i;
	int *visitedNodes;

	distance = calloc(size - 1, sizeof(int));
	visitedNodes = calloc(size - 1, sizeof(int));

	while (!full(visitedNodes, size)) {
		List *adjacency;
		visitedNodes[current] = 1;
		adjacency = graph->table[current].outlist;
		printf("Adjacency is\n");
		while (adjacency != NULL) {
			printf("%d\n", adjacency->index);
			if (distance[adjacency->index] > distanceVal && distance[adjacency->index] != 0) {
				distance[adjacency->index] = distanceVal;
			} else if (distance[adjacency->index] == 0) {
				distance[adjacency->index] = distanceVal;
			}
			adjacency = adjacency->next;
		}

		i = 1;
		//we find an initial minimum value
		while (i < size) {
			if (distance[i] != 0 && visitedNodes[i] == 0) {
				printf("distance : %d\n", distance[i]);
				minVal = distance[i];
				minIndex = i;
				break;
			}
			i++;
		}

		//now we loop again to find the minimum
		for (i = 1; i < size; i++) {
			if (visitedNodes[i] == 0 && distance[i] != 0) {
				if (distance[i] <= minVal) {
					minVal = distance[i];
					minIndex = i;
				}
			}
		}

		printf("Min is %d with val %d\n", minIndex, minVal);
		current = minIndex;
		printf("Current is %d\n", current);
		distanceVal++;
	}

	printf("Distances from %d are\n", start);
	for (i = 1; i < size; i++) {
		if (i != start) {
			printf("%d , %d\n", i, distance[i]);
		}
	}
}

int checkList(int target, Node node) {

	List *list = node.outlist;

	while (list != NULL) {
		if (list->index == node.index) {
			return 0;
		}
		list = list->next;
	}

	return 1;
}


Node findMax(List *list, Graph *graph) {

	int max = 0;
	Node node;

	while (list != NULL) {
		if (graph->table[list->index].outdegree > max) {
			max = graph->table[list->index].outdegree;
			node = graph->table[list->index];
		}
		list = list->next;
	}

	return node;
}

void heuristicSearch(Graph *graph, int target) {

	Node current = graph->table[1];
	Node *path = (Node *) malloc(graph->MaxSize * sizeof(Node));
	List *adjacency = current.outlist;
	int i = 1;

	printf("First node is %d\n", current.index);

	while (checkList(target, current) && adjacency != NULL) {
		path[i] = current;
		//printf("Path is %d\n", current.index);
		i++;
		current = findMax(current.outlist, graph);
		adjacency = current.outlist;
	}
	path[i] = current;

	printf("Shortest path\n");
	for (i = 1; i < graph->MaxSize; i++)
		printf("%d\n", path[i].index);
}
