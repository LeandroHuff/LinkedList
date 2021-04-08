/*
 ============================================================================
 Name        : Linked List
 Author      : Leandro Daniel Huff
 Version     :
 Copyright   : 
 Description : A linked list implementation.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
  @brief Linked list structure type
*/
typedef struct st_LinkedList
{
  int data; //!< integer data value
  struct st_LinkedList *next; //!< pointer to next element

} LinkedList_t; //!< linked list struture type

LinkedList_t *pLinkedList = NULL; //!< pointer to linked list structure

void List(LinkedList_t *pFirst)
{
  for ( 
      LinkedList_t *item = pFirst ; 
      (item != NULL) ; 
      item = item->next 
    )
  {
    printf("%d ", item->data);        
  }

  printf("\n");
}

void Put(int value)
{
  LinkedList_t *item = Last(pLinkedList);

  if ( item == NULL )
  {
    item = (LinkedList_t*)calloc(1, sizeof(LinkedList_t));
    pLinkedList = item;
  }
  else
  {
    item->next = (LinkedList_t*)calloc(1, sizeof(LinkedList_t));
    item = item->next;
  }

  item->data = value;
}

void Sort(LinkedList_t *pFirst)
{
  for ( LinkedList_t *actual = pFirst; actual != NULL ; actual = actual->next)
  {
    for (LinkedList_t *item = actual->next ; item != NULL; item = item->next)
    {
      if (item->data < actual->data)
      {
        int tmp = actual->data;
        actual->data = item->data;
        item->data = tmp;
      }
    }
  }

  List(pFirst);
}

void Free(LinkedList_t *pFirst)
{
  LinkedList_t *item = pFirst;

  while (item != NULL)
  {
    LinkedList_t *next = item->next;
    free(item);
    item = next;
  }
}

/**
  @brief Function to treat linked list
*/
void print_entry(char *entry) 
{
  // PUT
	if ( strncmp(entry, "put ", 4) == 0 )
  {
    int value = atoi( &entry[4] );
    Put(value);
  }
  // LIST
  else if ( strncmp(entry, "list\n", 5) == 0 )
  {
    List(pLinkedList);
  }
  // SORT
  else if ( strncmp(entry, "sort\n", 5) == 0 )
  {
    Sort(pLinkedList);
  }
  // EXIT
  else if ( strncmp(entry, "exit\n", 5) == 0 )
  {
    Free(pLinkedList);
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