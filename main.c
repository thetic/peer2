/**
 * @file	main.c
 * @brief	Peer-2 assignment for TCSS 343
 * @author	Group 9: Chad Condon, Richard Hemingway, Phuc Nguyen, Jasmine Scott
 */

/*************************** PREPROCESSOR DIRECTIVES **************************/
#include <stdlib.h>		// for calloc()
#include <stdio.h>		// for printf()
#include "queue.h"

#define SMALLSIZE 10	// nodes in small test case	
#define LARGESIZE 100	// nodes in large test case

/***************************** GLOBAL DECLARATIONS ****************************/
const char ten[] = "ten.txt";
const char hundred[] = "hundred.txt";
int ** small;			// small test case adjacency matrix
int ** large;			// large test case adjacency matrix

/***************************** FUNCTION PROTOTYPES ****************************/
int ** initSmall(void);
int ** initLarge(void);
int ** initMatrix(int size);
int ** readGraph(const char * name, int size);
void printMatrix(int ** matrix, int size);
void addEdge(int ** matrix, int x, int y);
void dfs(int ** matrix, int size);
void dfs_r(int ** matrix, int size, int * seen, int index);
void bfs(int ** matrix, int size);

/********************************** FUNCTIONS *********************************/
int main(void)
{
	small = readGraph(ten, SMALLSIZE);
	printf("Small Graph (size %d)\n", SMALLSIZE);	// print small graph
	printMatrix(small, SMALLSIZE);
	printf("\nDepth First Search:\n");				// run dfs
	dfs(small, SMALLSIZE);
	printf("\nBreadth First Search\n");				// run bfs
	bfs(small, SMALLSIZE);

	large = readGraph(hundred, LARGESIZE);
	printf("Large Graph (size %d)\n", LARGESIZE);	// print large graph
	printMatrix(large, LARGESIZE);
	printf("\nDepth First Search:\n");				// run dfs
	dfs(large, LARGESIZE);
	printf("\nBreadth First Search\n");				// run bfs
	bfs(large, LARGESIZE);
}

int ** readGraph(const char * name, int size)
{
	int ** ret = initMatrix(size);
	
	FILE * file;
	file = fopen(name, "r");
	
	if (file == NULL) {
		fprintf(stderr, "Can't open input file %s", name);
		exit (1);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if(!fscanf(file, "%d", &ret[i][j])) {
				break;
			}
		}
	}
	return ret;
}

/**
 * @brief Allocates an empty adacency matrix
 * @details Allocates memory for an empty square adjacency matrix
 * 
 * @param matrix pointer
 * @param size number of nodes
 */
int ** initMatrix(int size)
{
	int ** ret = calloc(size, sizeof(int *));		// allocate an array
	for (int i = 0; i < size; i++) {				// each subarrays
		ret[i] = calloc(size, sizeof(int));			// initilize and sero
	}
	return ret;
}

/**
 * @brief Prints an adjacency matric
 * @details Prints a square adjacency matrix of ones and zeros
 * 
 * @param matrix adjacency matrix
 * @param size number of columns and rows
 */
void printMatrix(int ** matrix, int size)
{
	for (int i = 0; i < size; i++) {				// each row
		for (int j = 0; j < size; j++) {			// each entry in row
			printf("%d", matrix[i][j]);				// print entry
		}
		printf("\n");
	}
}

/**
 * @brief depth first search
 * @details recursive depth first search
 * of a graph stored in an adjacency matrix
 * 
 * @param matrix adjacency matrix
 * @param size number of nodes
 */
void dfs(int ** matrix, int size)
{
	int * seen = calloc(size, sizeof(int));		// for tracking visited nodes
	for (int i = 0; i < size; i++) {			// for every node
		if (!seen[i]) {							// if unvisited
			dfs_r(matrix, size, seen, 0);		// initiate dfs recursion
		}
	}
	free(seen);									// destroy visited array
}


/**
 * @brief recursive depth first search
 * @details recursive depth first search
 * of a graph stored in an adjacency matrix
 * 
 * @param matrix adjacency matrix
 * @param size number of nodes
 * @param seen array storing which nodes have been seen
 * @param index index of the node to search
 */
void dfs_r(int ** matrix, int size, int * seen, int index)
{
	seen[index] = 1;								// mark node visited
	printf("%d\n", index);							// print node index
	for (int i = 0; i < size; i++) {				// check each connection
		if (!seen[i] && matrix[index][i]) {			// not visted and connected
			dfs_r(matrix, size, seen, i);			// recurse
		}
	}
}

/**
 * @brief breadth first search
 * @details breadth first search of an undirected graph
 * stored in an adjacency matrix
 * 
 * @param matrix adjacency matrix
 * @param size number of nodes
 */
void bfs(int ** matrix, int size)
{
	int * seen = calloc(size, sizeof(int));				// for tracking visited nodes
	for (int i = 0; i < size; i++) {
		if (!seen[i]) {
			queue * q = newQueue();						// create queue
			enqueue(q, 0);								// begin at node 0
			seen[0] = 1;								// mark node 0 visited
			while (!queueIsEmpty(q)) {					// while queue is not empty
				int curr = dequeue(q);					// dequeue a node
				printf("%d\n", curr);					// print its index
				for (int j = 0; j < size; j++) {		// check for connections
					if (!seen[j] && matrix[curr][j]) {	// not visted and connected
						enqueue(q, j);					// enqueue
						seen[j] = 1;					// mark visited
					}
				}
			}
			destroyQueue(q);							// destroy queue
		}
	}
}
