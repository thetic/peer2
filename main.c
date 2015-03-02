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

/***************************** STRUCTURES*************************************/
typedef struct{			//holds graph test data
	char * file;		//file name
	char * name;		//name to print
	const int size;		//number of nodes
	int ** matrix;		//adjacency matrix
} graph; 

/***************************** FUNCTION PROTOTYPES ****************************/
int ** initMatrix(int size);
int ** readGraph(const char * name, int size);
void printMatrix(int ** matrix, int size);
void dfs(int ** matrix, int size);
void dfs_r(int ** matrix, int size, int * seen, int index);
void bfs(int ** matrix, int size);

/********************************** FUNCTIONS *********************************/
int main(void)
{
	graph graphTest[2] = {
		{"ten.txt", "Small", SMALLSIZE},						//initialize struct with test files
		{"hundred.txt", "Large", LARGESIZE}
	};
	
	for(int i = 0; i < 2 /*sizeof(graphTest[i])*/; i++){				//iterate through test files
		graphTest[i].matrix = readGraph(graphTest[i].file, graphTest[i].size); //load graph matrix
		printf("%s Graph (size %d)\n", graphTest[i].name, graphTest[i].size);  //print heading
		printMatrix(graphTest[i].matrix, graphTest[i].size);	//print graph matrix
		
		printf("\nDepth First Search:\n");						// run dfs
		dfs(graphTest[i].matrix, graphTest[i].size);
	
		printf("\nBreadth First Search:\n");					// run bfs
		bfs(graphTest[i].matrix, graphTest[i].size);
	}
}

/**
 * @brief	loads adjacency matrix from file
 * @details	populates an adjacency matrix from a text file into an integer array
 * 
 * @param name	filename
 * @param size	number of nodes
 * 
 * @return pointer
 */
int ** readGraph(const char * name, int size)
{
	int ** ret = initMatrix(size);					// adjacency matrix
	FILE * file = fopen(name, "r");					// text file
	
	if (file == NULL) {								// check that file exists
		fprintf(stderr, "Can't open input file %s", name);
		exit (1);
	}

	// load each element
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (!fscanf(file, "%d", &ret[i][j])) {
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
	printf("Visited: %d\n", index);					// print node index when pushed
	for (int i = 0; i < size; i++) {				// check each connection
		if (!seen[i] && matrix[index][i]) {			// not visted and connected
			dfs_r(matrix, size, seen, i);			// recurse
		}
	}
	printf("Popped: %d\n", index);					//print when vertex is popped 
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
