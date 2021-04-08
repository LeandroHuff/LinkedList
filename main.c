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

/****************************************************************************
  HEADERS INCLUDES
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************************************************
  DEFINES
*****************************************************************************/


/****************************************************************************
  USER TYPEDEFS
*****************************************************************************/
typedef struct st_LinkedList
{
  int data; //!< integer data value
  struct st_LinkedList *next; //!< pointer to next element

} LinkedList_t; //!< linked list struture type

/****************************************************************************
  MODULE VARIABLES
*****************************************************************************/
LinkedList_t *pLinkedList = NULL; //!< pointer to linked list structure

/****************************************************************************
  FUNCTION PROTOTYPES
*****************************************************************************/
void print_entry(char *);


void Put(int);
LinkedList_t* Get(LinkedList_t*, int);
void Sort(LinkedList_t *);
void List(LinkedList_t *);
LinkedList_t* Last(LinkedList_t *);
void Remove(LinkedList_t **, int );
void Clear(LinkedList_t **);
void Free(LinkedList_t *);

/****************************************************************************
  FUNCTION IMPLEMENTATION
*****************************************************************************/

/**
 *  @brief Function to insert a new item into the linked list.
 *  @param iValue Value to be added to the linked list.
 *  @return Nothing
 */
void Put(int iValue)
{
  //Get the last item from the linked list.
  LinkedList_t *item = Last(pLinkedList);

  ///Check empty list and add the firs one
  if ( item == NULL )
  {
    item = (LinkedList_t*)calloc(1, sizeof(LinkedList_t));
    pLinkedList = item;
  }
  //Otherwise, add a new item to the end of linked list.
  else
  {
    item->next = (LinkedList_t*)calloc(1, sizeof(LinkedList_t));
    item = item->next;
  }

  //Store data value.
  item->data = iValue;
}

/**
  * @brief Function to get the n-esimo item from the linked list starting from 1.
  * @param pFirst Pointer address to the first item.
  * @param int iItem nth item to be gettered.
  * @return LinkedList_t* Item address from the linked list.
  */
LinkedList_t* Get(LinkedList_t *pFirst, int iItem)
{
  int iPos;
  LinkedList_t *item = NULL;

  if (iItem == 0)
  {
    return item;
  }
    
  for 
  ( 
    item = pFirst, iPos = 1;             /* get first item address, load firs item index */
    ((item != NULL) && (iPos < iItem)) ; /* not NULL and not reached the item            */
    item = item->next, iPos++            /* go to next item, inc position/index counter  */
  )
  {
    ; //just run until reached the item.
  }

  //Return nth item
  return item;
}

/**
  * @brief Function to get the n-esimo item from the linked list starting from 1.
  * @param pFirst Pointer address to the first item.
  * @param int iItem nth item to be gettered.
  * @return LinkedList_t* Item address from the linked list.
  */
void Remove(LinkedList_t **pFirst, int iItem)
{
  int iPos;
  LinkedList_t *pItem = NULL;
  LinkedList_t *pPrevious = NULL;

  //Wrong parameter value.
  if (iItem == 0)
  {
    return;
  }
    
  for 
  ( 
    pItem = *pFirst, iPos = 1;            /* get first item address, load firs item index */
    ((pItem != NULL) && (iPos < iItem)) ; /* not NULL and not reached the item            */
    pItem = pItem->next, iPos++           /* go to next item, inc position/index counter  */
  )
  {
    pPrevious = pItem; //store previous item address and run until reached the item.
  }
 
  //Found nth item
  if ((pItem != NULL) && (iPos == iItem))
  {
    //Isn't it first on the list.
    if (iPos > 1)
    {
      pPrevious->next = pItem->next;
      printf("item:%d  value:%d  removed!\n", iPos, pItem->data);
      free(pItem);
    }
    //Otherwise, remove the first one from the list.
    else
    {
      LinkedList_t *pTemp = pItem;
      *pFirst = pItem->next;
      printf("item:%d  value:%d  removed!\n", iPos, pTemp->data);
      free(pTemp);
    }

    //Show all linked list data.
    List(*pFirst);
  }
}

/**
 *  @brief Function to organize the data order from minor to greater values and
 *         print them on the stdout screen after reordered.
 *  @param pFirst Pointer to first item of linked list.
 *  @return Nothing
 */
void Sort(LinkedList_t *pFirst)
{
  //Get address of first item from the linked list and follow each item from the list.
  for ( LinkedList_t *actual = pFirst; actual != NULL ; actual = actual->next)
  {
    //At the the specific item up to the end for each one,
    //check which one is smaller then next one and change them.
    for (LinkedList_t *item = actual->next ; item != NULL; item = item->next)
    {
      //Check smaller item and change them.
      if (item->data < actual->data)
      {
        int tmp = actual->data;
        actual->data = item->data;
        item->data = tmp;
      }
    }
  }

  //Print the linked list data on the stdout.
  List(pFirst);
}

/**
 *  @brief Function to print all elements of a linked list on stdout terminal screen.
 *  @param pFirst Pointer to first item.
 *  @return Nothing.
 */
void List(LinkedList_t *pFirst)
{
  for ( 
      LinkedList_t *item = pFirst ; /* get first item address        */
      (item != NULL) ;              /* while its not a NULL pointer  */
      item = item->next             /* go to next item into the list */
    )
  {
    //Print data value from the item.
    printf("%d ", item->data);
  }

  //Print a new line at the end of list.
  printf("\n");
}

/**
 *  @brief Function to print all elements of a linked list on stdout terminal screen.
 *  @param pFirst Pointer to first item.
 *  @return LinkedList_t* Pointer to the last item into linked list.
 */
LinkedList_t* Last(LinkedList_t *pFirst)
{
  LinkedList_t *item = NULL;

  for (
        item = pFirst;                            /* get the first item            */
        ((item != NULL) && (item->next != NULL)); /* while it's not the last one   */
        item = item->next                         /* go to next item into the list */
      )
  {
    ; //Run until find the last item into the linked list.
  }

  return item;
}

/**
  * @brief Function to release all data on linked list.
  * @param ppFirst Pointer to pointer to the first item of linked list.
  * @return Nothing.
  */
void Clear(LinkedList_t **ppFirst)
{
  Free(*ppFirst); //Call function to release all allocated memory.
  *ppFirst = NULL;//Clear linked list pointer.
}

/**
 *  @brief Function to release previous memory allocation for linked list items.
 *  @param pFirst Pointer to first item of linked list.
 *  @return Nothing.
 */
void Free(LinkedList_t *pFirst)
{
  //Get first item address
  LinkedList_t *item = pFirst;

  //From the first item until the end, release each one item.
  while (item != NULL)
  {
    LinkedList_t *next = item->next;  //store next item address
    free(item);                       //release memory address of current item
    item = next;                      //go to next item
  }
}

/**
 *  @brief Function to treat linked list commands from stdin.
 *  @param entry Pointer to string buffer.
 *  @return Nothing.
 */
void print_entry(char *entry) 
{
  // PUT n
	if ( strncmp(entry, "put ", 4) == 0 )
  {
    int value = atoi( &entry[4] );
    Put(value);
  }
  // GET n
	if ( strncmp(entry, "get ", 4) == 0 )
  {
    int iItem = atoi( &entry[4] );
    LinkedList_t *pItem = Get(pLinkedList, iItem);

    if (pItem != NULL)
    {
      printf("%d\n", pItem->data);
    }
  }
  // LIST
  else if ( strncmp(entry, "list\n", 5) == 0 )
  {
    List(pLinkedList);
  }
  //FIRST
  else if ( strncmp(entry, "first\n", 6) == 0 )
  {
    LinkedList_t *pItem = pLinkedList;

    if (pItem != NULL)
    {
      printf("%d\n", pItem->data);
    }
  }
  // LAST
  else if ( strncmp(entry, "last\n", 5) == 0 )
  {
    LinkedList_t *pItem = Last(pLinkedList);

    if (pItem != NULL)
    {
      printf("%d\n", pItem->data);
    }
  }
  // SORT
  else if ( strncmp(entry, "sort\n", 5) == 0 )
  {
    Sort(pLinkedList);
  }
  // REMOVE n
	if ( strncmp(entry, "remove ", 7) == 0 )
  {
    int item = atoi( &entry[7] );
    Remove(&pLinkedList, item);
  }
  // CLEAR
  else if ( strncmp(entry, "clear\n", 6) == 0 )
  {
    Clear(&pLinkedList);
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