#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"

int isArrayFilled(int *array, int size) {

	int i;

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
	int *nodeDistances;
	int *visitedNodes;
	int currentIndex = start;
	int distanceUntilNow = 1;
	int minDistance, minIndex;
	int i;

	/* When distance between nodes is 0, there is no known connection. */
	nodeDistances = calloc(size, sizeof(int));
	visitedNodes = calloc(size, sizeof(int));

	while (1) {
		List *adjacency;
		adjacency = graph->table[currentIndex].outlist;
		visitedNodes[currentIndex] = 1;

		printf("Adjacency is\n");
		while (adjacency != NULL) {
			printf("%d\n", adjacency->index);
			if (nodeDistances[adjacency->index] > distanceUntilNow && nodeDistances[adjacency->index] != 0) {
				nodeDistances[adjacency->index] = distanceUntilNow;
			} else if (nodeDistances[adjacency->index] == 0) {
				nodeDistances[adjacency->index] = distanceUntilNow;
			}
			adjacency = adjacency->next;
		}

		/* We loop to find the minimum node. */
		minDistance = INT_MAX;
		minIndex = -1;
		for (i = 1; i < size; i++) {
			if (nodeDistances[i] != 0 && visitedNodes[i] == 0) {
				if (nodeDistances[i] <= minDistance) {
					minDistance = nodeDistances[i];
					minIndex = i;
				}
			}
		}

		/*
		 * Loop exit conditions:
		 *   * no more connected nodes starting from start
		 *   * all nodes are now visited
		 */
		if (minIndex == -1)
			break;
		if (isArrayFilled(visitedNodes, size))
			break;

		printf("Minimum node index is %d with distance %d from start index %d\n", minIndex, minDistance, start);
		currentIndex = minIndex;
		printf("Current node index is %d\n", currentIndex);
		distanceUntilNow++;
	}

	printf("Distances from %d are\n", start);
	for (i = 1; i < size; i++) {
		if (i != start) {
			printf("%d , %d\n", i, nodeDistances[i]);
		}
	}

	free(nodeDistances);
	free(visitedNodes);
}

/*
 * Check if node index (index parameter) is adjacent to node. Look
 * through node adjacency list; return 1 (true) if node index is part
 * of the adjanceny list and 0 (false) otherwise.
 */

int isNodeIndexAdjacent(Node *node, int index) {

	List *list = node->outlist;
	/* Check if current node is the index node. */
	if (node->index == index)
		return 1;

	/* Check if index node is in adjacency list. */
	while (list != NULL) {
		if (list->index == index)
			return 1;
		list = list->next;
	}

	return 0;
}


/*
 * Find the next unvisited node with the maximum out degree.
 */

Node *findMaxOutDegreeNode(Node *node, Graph *graph) {

	List *list = node->outlist;
	int max = 0;
	Node *current = NULL;

	while (list != NULL) {
		/*
		 * Check if node in adjancecy list is not current node.
		 * Select node with maximum outdegree from the rest
		 */
		if (list->index != node->index && graph->table[list->index].state == 0 && graph->table[list->index].outdegree > max) {
			max = graph->table[list->index].outdegree;
			current = &graph->table[list->index];
		}
		list = list->next;
	}

	return current;
}


/*
 * Mark all graph nodes as unvisited.
 */

void markNodesAsUnvisited(Graph *graph) {

	int i;

	for (i = 1; i <= graph->MaxSize; i++)
		graph->table[i].state = 0;
}


void heuristicSearch(Graph *graph, int target) {

	Node *current = &graph->table[1];
	Node **path = (Node **) malloc(graph->MaxSize * sizeof(Node *));
	int i = 0;
	int path_len = 0;

	/*
	printf("First node is %d\n", current->index);
	printf("current->outlist %p\n", current->outlist);
	printf("isNodeIndexAdjacent(%d, %d): %d\n", current->index, target, isNodeIndexAdjacent(current, target));
	*/

	while (!isNodeIndexAdjacent(current, target)) {
		path[path_len] = current;
		//printf("Path is %d\n", current->index);
		path_len++;
		current->state = 1;
		current = findMaxOutDegreeNode(current, graph);
		if (current == NULL)
			break;
	}
	path[path_len] = current;
	path_len++;

	if (current != NULL && isNodeIndexAdjacent(current, target)) {
		if (current->index != target) {
			path[path_len] = &graph->table[target];
			path_len++;
		}
		printf("Shortest path from node %d to %d: [ ", 1, target);
		for (i = 0; i < path_len; i++) {
			if (path[i]->index == 0)
				break;
			printf("%d ", path[i]->index);
		}
		printf("]\n");
	}
	else
		printf("No path from node %d to %d.\n", 1, target);

	free(path);
	markNodesAsUnvisited(graph);
}
