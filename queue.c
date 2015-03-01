/**
 * @file queue.c
 * @brief simple queue data structure for integers
 * @author Group-9: Chad Condon, Richard Hemingway, Phuc Nguyen, Jasmine Scott
 */

/*************************** PREPROCESSOR DIRECTIVES **************************/
#include "queue.h"

/********************************** FUNCTIONS *********************************/
/**
 * @brief node constructor
 * @details creates a new queue node
 * 
 * @param value integer value held in the node
 * @return pointer to the node
 */
queue_node * newNode(int value)
{
	queue_node * ret = (queue_node *) malloc(sizeof(queue_node));
	ret->val = value;								// set value
	ret->next = NULL;								// set no net node
	return ret;
}

/**
 * @brief node destructor
 * @details destroys a node
 * 
 * @param node queue node to be destroyed
 * @return value held in the destroyed node
 */
int destroyNode(queue_node * node)
{
	int ret = node->val;							// get value
	free(node);										// deallocate memory
	return ret;
}

/**
 * @brief queue constructor
 * @details creates a new empty queue
 * 
 * @return pointer to the queue
 */
queue * newQueue(void)
{
	queue * ret = (queue *) malloc(sizeof(queue));	// allocate memory
	ret->first = NULL;								// set no first node
	ret->last = NULL;								// set no last node
	return ret;
}

/**
 * @brief queue destructor
 * @details destroys a queue and its nodes
 * 
 * @param q queue to be destroyed
 */
void destroyQueue(queue * q)
{
	if(!q) return;									// check for null queue
	queue_node * curr = q->first;					// begin at first
	queue_node * next;								// holder pointed
	while (curr) {									// while nodes exist
		next = curr->next;							// hold next
		destroyNode(curr);							// free node
		curr = next;								// update pointer
	}
	free(q);
}

/**
 * @brief determines whether a queue is empty
 * 
 * @param q the queue
 * @return 0 if the queue has nodes and 1 if it has no nodes
 */
int queueIsEmpty(queue * q)
{
	if (q->first) {
		return 0;
	}
	return 1;
}

/**
 * @brief adds a node to the queue
 * @details creates a node holding the given value
 * and adds it to the end of the queue
 * 
 * @param q the queue
 * @param value integer value to be addded to the queue
 */
void enqueue(queue * q, int value)
{
	queue_node * new = newNode(value);				// create new node
	if (queueIsEmpty(q)) {							// if empty, first and last
		q->first = new;
		q->last = new;
	} else {										// otherwise last
		q->last->next = new;
		q->last = new;
	}
}

/**
 * @brief removes a node from the queue
 * @details removes the first node from the queue
 * 
 * @param q the queue
 * @return the integer value held in the removed node
 */
int dequeue(queue * q)
{
	if (queueIsEmpty(q))							// check for empty queue
		return -1;
	queue_node * del = q->first;					// hold node
	int ret = del->val;								// hold its value
	q->first = del->next;							// set new first node
	destroyNode(del);								// destroy old first
	return ret;
}
