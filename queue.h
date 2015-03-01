/**
 * @file queue.h
 * @brief simple queue data structure for integers
 * @author Group-9: Chad Condon, Richard Hemingway, Phuc Nguyen, Jasmine Scott
 */

/*************************** PREPROCESSOR DIRECTIVES **************************/
#include <stdlib.h>	// for malloc()

/***************************** GLOBAL DECLARATIONS ****************************/
/**
 * @brief queue node structure
 * 
 */
struct queue_node
{
	int val;					// node value
	struct queue_node * next;	// next queue node
};
typedef struct queue_node queue_node;

/**
 * @brief queue data structure for integers
 */
struct queue
{
	queue_node * first;			// first node
	queue_node * last;			// last node
};
typedef struct queue queue;

/***************************** FUNCTION PROTOTYPES ****************************/
queue_node * newNode(int value);
int destroyNode(queue_node * node);
queue * newQueue(void);
void destroyQueue(queue * q);
int queueIsEmpty(queue * q);
void enqueue(queue * q, int value);
int dequeue(queue * q);
