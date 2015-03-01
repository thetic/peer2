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
int ** small;			// small test case adjacency matrix
int ** large;			// large test case adjacency matrix

/***************************** FUNCTION PROTOTYPES ****************************/
int ** initSmall(void);
int ** initLarge(void);
int ** initMatrix(int size);
void printMatrix(int ** matrix, int size);
void addEdge(int ** matrix, int x, int y);
void dfs(int ** matrix, int size);
void dfs_r(int ** matrix, int size, int * seen, int index);
void bfs(int ** matrix, int size);

/********************************** FUNCTIONS *********************************/
int main(void)
{
	small = initSmall();							// initialize small graph
	printf("Small Graph (size %d)\n", SMALLSIZE);	// print small graph
	printMatrix(small, SMALLSIZE);
	printf("\nDepth First Search:\n");				// run dfs
	dfs(small, SMALLSIZE);
	printf("\nBreadth First Search\n");				// run bfs
	bfs(small, SMALLSIZE);

	large = initLarge();							// initialize large graph
	printf("Large Graph (size %d)\n", LARGESIZE);	// print large graph
	printMatrix(large, LARGESIZE);
	printf("\nDepth First Search:\n");				// run dfs
	dfs(large, LARGESIZE);
	printf("\nBreadth First Search\n");				// run bfs
	bfs(large, LARGESIZE);
}

/**
 * @brief	Creates a small adjacency matrix
 * @details	Allocates and populates an adjacency matrix
 * 			for a small undirected graph
 * 
 * @return	populated adjacency matrix
 */
int ** initSmall(void)
{
	int ** ret = initMatrix(SMALLSIZE);				// allocated memory
	// Populate as binary heap
	addEdge(ret, 0, 1);
	addEdge(ret, 0, 2);
	addEdge(ret, 1, 3);
	addEdge(ret, 1, 4);
	addEdge(ret, 2, 5);
	addEdge(ret, 2, 6);
	addEdge(ret, 3, 7);
	addEdge(ret, 3, 8);
	addEdge(ret, 4, 9);
	return ret;
}

/**
 * @brief Creates a large adjacency matrix
 * @details Allocates and populates an adjacency matrix
 * for a large undirected graph
 * 
 * @return populated adjacency matrix
 */
int ** initLarge(void)
{
	int ** ret = initMatrix(LARGESIZE);				// allocate memory
	/*
	 * populated in a lattice as shown below
	 *                   0
	 *                  / \
	 *                 1   2
	 *                / \ / \
	 *               3   4   5
	 *              / \ / \ / \
	 *             6   7   8   9
	 *            / \ / \ / \ / \
	 *                   .
	 *                   .
	 *                   .
	 */
	addEdge(ret, 0, 1);
	addEdge(ret, 0, 2);
	addEdge(ret, 1, 3);
	addEdge(ret, 1, 4);
	addEdge(ret, 2, 4);
	addEdge(ret, 2, 5);
	addEdge(ret, 3, 6);
	addEdge(ret, 3, 7);
	addEdge(ret, 4, 7);
	addEdge(ret, 4, 8);
	addEdge(ret, 5, 8);
	addEdge(ret, 5, 9);
	addEdge(ret, 6, 10);
	addEdge(ret, 6, 11);
	addEdge(ret, 7, 11);
	addEdge(ret, 7, 12);
	addEdge(ret, 8, 12);
	addEdge(ret, 8, 13);
	addEdge(ret, 9, 13);
	addEdge(ret, 9, 14);
	addEdge(ret, 10, 15);
	addEdge(ret, 10, 16);
	addEdge(ret, 11, 16);
	addEdge(ret, 11, 17);
	addEdge(ret, 12, 17);
	addEdge(ret, 12, 18);
	addEdge(ret, 13, 18);
	addEdge(ret, 13, 19);
	addEdge(ret, 14, 19);
	addEdge(ret, 14, 20);
	addEdge(ret, 15, 21);
	addEdge(ret, 15, 22);
	addEdge(ret, 16, 22);
	addEdge(ret, 16, 23);
	addEdge(ret, 17, 23);
	addEdge(ret, 17, 24);
	addEdge(ret, 18, 24);
	addEdge(ret, 18, 25);
	addEdge(ret, 19, 25);
	addEdge(ret, 19, 26);
	addEdge(ret, 20, 26);
	addEdge(ret, 20, 27);
	addEdge(ret, 21, 28);
	addEdge(ret, 21, 29);
	addEdge(ret, 22, 29);
	addEdge(ret, 22, 30);
	addEdge(ret, 23, 30);
	addEdge(ret, 23, 31);
	addEdge(ret, 24, 31);
	addEdge(ret, 24, 32);
	addEdge(ret, 25, 32);
	addEdge(ret, 25, 33);
	addEdge(ret, 26, 33);
	addEdge(ret, 26, 34);
	addEdge(ret, 27, 34);
	addEdge(ret, 27, 35);
	addEdge(ret, 28, 36);
	addEdge(ret, 28, 37);
	addEdge(ret, 29, 37);
	addEdge(ret, 29, 38);
	addEdge(ret, 30, 38);
	addEdge(ret, 30, 39);
	addEdge(ret, 31, 39);
	addEdge(ret, 31, 40);
	addEdge(ret, 32, 40);
	addEdge(ret, 32, 41);
	addEdge(ret, 33, 41);
	addEdge(ret, 33, 42);
	addEdge(ret, 34, 42);
	addEdge(ret, 34, 43);
	addEdge(ret, 35, 43);
	addEdge(ret, 35, 44);
	addEdge(ret, 36, 45);
	addEdge(ret, 36, 46);
	addEdge(ret, 37, 46);
	addEdge(ret, 37, 47);
	addEdge(ret, 38, 47);
	addEdge(ret, 38, 48);
	addEdge(ret, 39, 48);
	addEdge(ret, 39, 49);
	addEdge(ret, 40, 49);
	addEdge(ret, 40, 50);
	addEdge(ret, 41, 50);
	addEdge(ret, 41, 51);
	addEdge(ret, 42, 51);
	addEdge(ret, 42, 52);
	addEdge(ret, 43, 52);
	addEdge(ret, 43, 53);
	addEdge(ret, 44, 53);
	addEdge(ret, 44, 54);
	addEdge(ret, 45, 55);
	addEdge(ret, 45, 56);
	addEdge(ret, 46, 56);
	addEdge(ret, 46, 57);
	addEdge(ret, 47, 57);
	addEdge(ret, 47, 58);
	addEdge(ret, 48, 58);
	addEdge(ret, 48, 59);
	addEdge(ret, 49, 59);
	addEdge(ret, 49, 60);
	addEdge(ret, 50, 60);
	addEdge(ret, 50, 61);
	addEdge(ret, 51, 61);
	addEdge(ret, 51, 62);
	addEdge(ret, 52, 62);
	addEdge(ret, 52, 63);
	addEdge(ret, 53, 63);
	addEdge(ret, 53, 64);
	addEdge(ret, 54, 64);
	addEdge(ret, 54, 65);
	addEdge(ret, 55, 66);
	addEdge(ret, 55, 67);
	addEdge(ret, 56, 67);
	addEdge(ret, 56, 68);
	addEdge(ret, 57, 68);
	addEdge(ret, 57, 69);
	addEdge(ret, 58, 69);
	addEdge(ret, 58, 70);
	addEdge(ret, 59, 70);
	addEdge(ret, 59, 71);
	addEdge(ret, 60, 71);
	addEdge(ret, 60, 72);
	addEdge(ret, 61, 72);
	addEdge(ret, 61, 73);
	addEdge(ret, 62, 73);
	addEdge(ret, 62, 74);
	addEdge(ret, 63, 74);
	addEdge(ret, 63, 75);
	addEdge(ret, 64, 75);
	addEdge(ret, 64, 76);
	addEdge(ret, 65, 76);
	addEdge(ret, 65, 77);
	addEdge(ret, 66, 78);
	addEdge(ret, 66, 79);
	addEdge(ret, 67, 79);
	addEdge(ret, 67, 80);
	addEdge(ret, 68, 80);
	addEdge(ret, 68, 81);
	addEdge(ret, 69, 81);
	addEdge(ret, 69, 82);
	addEdge(ret, 70, 82);
	addEdge(ret, 70, 83);
	addEdge(ret, 71, 83);
	addEdge(ret, 71, 84);
	addEdge(ret, 72, 84);
	addEdge(ret, 72, 85);
	addEdge(ret, 73, 85);
	addEdge(ret, 73, 86);
	addEdge(ret, 74, 86);
	addEdge(ret, 74, 87);
	addEdge(ret, 75, 87);
	addEdge(ret, 75, 88);
	addEdge(ret, 76, 88);
	addEdge(ret, 76, 89);
	addEdge(ret, 77, 89);
	addEdge(ret, 77, 90);
	addEdge(ret, 78, 91);
	addEdge(ret, 78, 92);
	addEdge(ret, 79, 92);
	addEdge(ret, 79, 93);
	addEdge(ret, 80, 93);
	addEdge(ret, 80, 94);
	addEdge(ret, 81, 94);
	addEdge(ret, 81, 95);
	addEdge(ret, 82, 95);
	addEdge(ret, 82, 96);
	addEdge(ret, 83, 96);
	addEdge(ret, 83, 97);
	addEdge(ret, 84, 97);
	addEdge(ret, 84, 98);
	addEdge(ret, 85, 98);
	addEdge(ret, 85, 99);
	addEdge(ret, 86, 99);

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
 * @brief adds an edge to the graph
 * @details adds an edge to an undirected graph stored in an adjacency matrix
 * 
 * @param matrix adjacency matrix
 * @param x node 1 index
 * @param y node 2 index
 */
void addEdge(int ** matrix, int x, int y)
{
	// add both connections for undirected graph
	matrix[x][y] = 1;
	matrix[y][x] = 1;
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
	for (int i = 0; i < size; i ++) {			// for every node
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
				for (int i = 0; i < size; i++) {		// check for connections
					if (!seen[i] && matrix[curr][i]) {	// not visted and connected
						enqueue(q, i);					// enqueue
						seen[i] = 1;					// mark visited
					}
				}
			}
			destroyQueue(q);							// destroy queue
		}
	}
}
