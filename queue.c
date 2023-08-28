/*
 * This file is where you should implement your queue.  It already contains
 * skeletons of the functions you need to implement (along with documentation
 * for each function).  Feel free to implement any additional functions you
 * might need.  Also, don't forget to include your name and @oregonstate.edu
 * email address below.
 *
 * Name: Kaden Fugate
 * Email: fugateka@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "dynarray.h"

// check done

/*
 * This is the structure that will be used to represent a queue.  This
 * structure specifically contains a single field representing a dynamic array
 * that should be used as the underlying data storage for the queue.
 *
 * You should not modify this structure.
 */
struct queue 
{

  struct dynarray* array;

};

/*
 * This function should allocate and initialize a new, empty queue and return
 * a pointer to it.
 */
struct queue* queue_create() 
{
	
	struct queue *temp = malloc( sizeof( struct queue ) );

	temp->array = dynarray_create();

	return temp;
}

/*
 * This function displays the content of a whole queue.
 * ( used this function to make callcenter look nicer. would
 * usually just use (*p) queue_front() for what assignment asked )
 *
 * Params:
 * 		queue - queue to be displayed
 * 		p - function to print a caller
 *
 */
void display_queue( struct queue *queue, void (*p)(void*) )
{

	printf("Queue Contents: \n\n");
	print_arr(queue->array, p);

	if(queue_isempty(queue)){ printf("Empty!\n\n"); }

	printf("Calls to Answer: %d\n\n", arr_size(queue->array));

}

/*
 * This function should free the memory associated with a queue.  While this
 * function should up all memory used in the queue itself, it should not free
 * any memory allocated to the pointer values stored in the queue.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   queue - the queue to be destroyed.  May not be NULL.
 */
void queue_free(struct queue* queue)
{

	dynarray_free(queue->array);
	free(queue);

}

/*
 * This function should indicate whether a given queue is currently empty.
 * Specifically, it should return 1 if the specified queue is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   queue - the queue whose emptiness is being questioned.  May not be NULL.
 */
int queue_isempty(struct queue* queue) 
{

	return is_empty(queue->array);

}

/*
 * This function should enqueue a new value into a given queue.  The value to
 * be enqueued is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   queue - the queue into which a value is to be enqueued.  May not be NULL.
 *   val - the value to be enqueued.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void queue_enqueue(struct queue* queue, void* val) 
{
	
	dynarray_insert(queue->array, val); // insert at end

}

/*
 * This function should return the value stored at the front of a given queue
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   queue - the queue from which to query the front value.  May not be NULL.
 */
void* queue_front(struct queue* queue) 
{

	return arr_head(queue->array); // return head of arr
}

/*
 * This function should dequeue a value from a given queue and return the
 * dequeued value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   queue - the queue from which a value is to be dequeued.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_dequeue(struct queue* queue) 
{

	if( is_empty(queue->array) ){ return NULL; } // if arr is enpty, nothing to dequeue

	void *temp = queue_front(queue); // store val of object to be dequeued
	shift_a_head(queue->array); // increment head to dequeue
	
	return temp;

}
