/**
  @brief Linked List Algorithms
         Read user commands from stdin as:
         PUT n, GET n, LIST, FIRST, LAST, SORT, CLEAR, REMOVE n, EXIT
         and run functions over a linked list according to the user instruction.
  @author Leandro Daniel Huff
  @project Developed and Tested on https://replit.com/@LeandroHuff/LinkedList
  @date 2021/04/08 (AAAA/MM/DD)
  @file main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

void print_entry(char *entry) 
{
  if ( iLinkedListRun(entry) != 0 )
  {
    printf("Error\n");
  }
}

int main(int argc, char *argv[]) 
{
	char input[201];

	while(1) 
  {
		printf("prompt> ");

		if (fgets(input, 200, stdin) == NULL) 
    {
			printf("An error ocurred.\n");
			break;
		}

		if (strncmp(input, "exit\n", 5) == 0) 
    {
			printf("Leaving. Good bye.\n");
			break;
		}

		print_entry(input);
	}

	return EXIT_SUCCESS;
}