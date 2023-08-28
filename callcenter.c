/* This program allows the user to manage a call center
using stacks and queues. 
Name: Kaden "ator" Fugate
Email: fugateka@oregonstate.edu
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "stack.h"


struct caller
{

	int num;
	char *name;
	char *reason;

};

/* 
 * This function prints a caller struct
 *
 * Param:
 * 		val - caller
 *
*/
void print_caller(void* val)
{

	struct caller *caller = val; // set data type to be able to print

	printf("|   ID   | %d\n", caller->num);
	printf("|  Name  | %s\n", caller->name);
	printf("| Reason | %s\n\n", caller->reason);

}

/*
 * This function gets the info of a caller from
 * the user.
 *
 * Param:
 * 		type - string to tell program
 *		if entering name or reason
 *
*/
char* get_info(char *type)
{

	char *str;

	if(type == "name")
	{
		str = malloc( 20 * sizeof(char) ); // 20 chars for name
	}
	else{ str = malloc( 100 * sizeof(char) ); } // 100 chars for reason

	printf("Enter %s: ", type);
	scanf(" %[^\n]%*c", str); // <-- " %[^\n]%*c" gets a line instead of just one word
	printf("\n");

	return str;

}

/*
 * This function lets the user receive a call (i.e. add to queue)
 *
 * Params:
 * 		num - number of caller
 * 		queue - queue being added to
*/
void receive_call(int num, struct queue *queue)
{

	struct caller *caller = malloc ( sizeof (struct caller) );

	caller->num = num;
	caller->name = get_info("name"), caller->reason = get_info("reason"); // get name and reason

    queue_enqueue( queue, (void *) caller); // put caller into queue casted as void *

}

/*
 * This function lets the user answer a call (i.e. queue -> stack)
 * 
 * Params:
 * 		queue - queue being pulled from
 * 		stack - being added to
 */
void answer_call(struct queue *queue, struct stack *stack)
{

	stack_push(stack, queue_dequeue(queue));

	printf("Answered call: \n\n");
	print_caller( stack_top(stack) ); // print top of stack

}

/*
 * This function frees all of the memory within a caller struct
 * 
 * Param:
 * 		val - val being deleted
 */
void free_caller(void *val)
{
	struct caller *caller = val; // set val to caller
	free(caller->name), free(caller->reason);
	free(caller);
}

/*
 * This function will free all of the memory currently being
 * used by the program
 *
 * Params:
 * 		stack - stack being freed
 * 		queue - queue being freed
 */
void free_vars(struct stack *stack, struct queue *queue)
{
	/* free_caller (pop/dequeue) frees top of stack/ queue and frees
	caller mem. does this until whole stack + queue are freed */
	while(!stack_isempty(stack)){ free_caller( stack_pop( stack ) ); }
	while(!queue_isempty(queue)){ free_caller( queue_dequeue( queue ) ); }

	queue_free(queue);
	stack_free(stack);
}

int main(int argc, char const *argv[]) 
{

	// init vals
	struct queue *queue = queue_create();
	struct stack *stack = stack_create();
	int num = 0, choice;

	while(1)
	{
		// long statement prints options, gets choice
		printf("1. Receive a new call\n2. Answer a call\n3. Current state - Queue\n4. Current state - Stack\n5. Quit\n\nEnter a choice: ");
		scanf(" %d", &choice);
		printf("\n");

		if(choice == 1)
		{ 
			receive_call(num, queue); 
			num++; // when receive call, increment call num
		}
		else if(choice == 2)
		{ 
			// if empty, dont answer call
			if( queue_isempty(queue) ){ printf("No more calls need to be answered at the moment!\n\n"); continue; } 
			answer_call(queue, stack); 
		}
		else if(choice == 3)
		{ 
			display_queue(queue, &print_caller); 
		}
		else if(choice == 4){ 
			display_stack(stack, &print_caller); 
		}
		else if(choice == 5)
		{
			free_vars(stack, queue), break;
		}

	}
	
	return 0;
}
