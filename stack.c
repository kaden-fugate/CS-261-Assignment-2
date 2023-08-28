/*
 * This file is where you should implement your stack.  It already contains
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

#include "stack.h"
#include "list.h"

// check done

/*
 * This is the structure that will be used to represent a stack.  This
 * structure specifically contains a single field representing a linked list
 * that should be used as the underlying data storage for the stack.
 *
 * You should not modify this structure.
 */
struct stack 
{

	struct list* list;

};

/*
 * This function should allocate and initialize a new, empty stack and return
 * a pointer to it.
 */
struct stack* stack_create() 
{
	
	struct stack *temp = malloc ( sizeof ( struct stack ) );
	temp->list = list_create(); // func allocates mem to list

	return temp;

}

/*
 * This function should print all of the values in the stack. If
 * stack is empty, special message will be printed. func prints calls answered
 * 
 * Params:
 *		stack - stack to be printed
 *		p - function to print the caller info
 */
void display_stack( struct stack *stack, void (*p)(void*) )
{

	printf("Stack Contents: \n\n");
	print_list(stack->list, p); // func displays the linked list within the stack

	if(stack_isempty(stack)){ printf("Empty!\n\n"); } // if list is empty, special message

	printf("Calls Answered: %d\n\n", list_size(stack->list));

}

/*
 * This function should free the memory associated with a stack.  While this
 * function should up all memory used in the stack itself, it should not free
 * any memory allocated to the pointer values stored in the stack.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   stack - the stack to be destroyed.  May not be NULL.
 */
void stack_free(struct stack* stack) 
{
	
	list_free( stack->list ); // func frees mem in list
	free(stack);

}

/*
 * This function should indicate whether a given stack is currently empty.
 * Specifically, it should return 1 if the specified stack is empty (i.e.
 * contains no elements) and 0 otherwise.
 *
 * Params:
 *   stack - the stack whose emptiness is being questioned.  May not be NULL.
 */
int stack_isempty(struct stack* stack) 
{
	
	if( head_exists(stack->list) ){ return 0; } 

	return 1;

}

/*
 * This function should push a new value onto a given stack.  The value to be
 * pushed is specified as a void pointer.  This function must have O(1)
 * average runtime complexity.
 *
 * Params:
 *   stack - the stack onto which a value is to be pushed.  May not be NULL.
 *   val - the value to be pushed.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void stack_push(struct stack* stack, void* val) 
{

	list_insert( stack->list, val ); // func inserts node at front of stack

}

/*
 * This function should return the value stored at the top of a given stack
 * *without* removing that value.  This function must have O(1) average runtime
 * complexity.
 *
 * Params:
 *   stack - the stack from which to query the top value.  May not be NULL.
 */
void* stack_top(struct stack* stack) 
{

	return list_head(stack->list);

}

/*
 * This function should pop a value from a given stack and return the popped
 * value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   stack - the stack from which a value is to be popped.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was popped.
 */
void* stack_pop(struct stack* stack) 
{

	if(!head_exists(stack->list)){ return NULL; } // if not head, NULL
	void *temp = stack_top( stack ); // if head, store val O(1)

	shift_l_head(stack->list); // move head up and free old head

	return temp;

}
