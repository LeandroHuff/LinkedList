/**
  @brief Linked List Algorithms
         Read user commands from stdin as:
         PUT n, GET n, LIST, FIRST, LAST, SORT, CLEAR, REMOVE n, EXIT
         and run functions over a linked list according to the user instruction.
         Implementation of all linked list function and treaters.
  @author Leandro Daniel Huff
  @project Developed and Tested on https://replit.com/@LeandroHuff/LinkedList
  @date 2021/04/08 (AAAA/MM/DD)
  @file linkedlist.c
*/

/****************************************************************************
  HEADERS/INCLUDES
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

/****************************************************************************
  USER DEFINES
*****************************************************************************/
#define CHECK_NULL_PTR(pointer,ret) if(pointer == NULL) { return ret; }
#define CHECK_DIFF_INT(var,val,ret) if(var != val)      { return ret; }
#define CHECK_EQU_INT(var,val,ret)  if(var == val)      { return ret; }
#define UNUSED(var)                 (void)var;

/****************************************************************************
  USER TYPEDEFS
*****************************************************************************/
typedef struct st_LinkedList
{
  int data; //!< integer data value
  struct st_LinkedList *next; //!< pointer to next element

} LinkedList_t; //!< linked list struture type

//Function type
typedef int (*pLinkedListFunction_t)(LinkedList_t **, int); //!< Linked list function type treater

/****************************************************************************
  FUNCTION PROTOTYPES
*****************************************************************************/
int   Exit(LinkedList_t**, int); //!< EXIT - Release all allocated memory and exit.
int    Put(LinkedList_t**, int); //!< PUT num - Store num value into linked list.
int    Get(LinkedList_t**, int); //!< GET nth - Get nth data item from linked list.
int   Sort(LinkedList_t**, int); //!< SORT - Reorder data items into linked list.
int   List(LinkedList_t**, int); //!< LIST - Print all data items to stdout.
int  First(LinkedList_t**, int); //!< FIRST - Print first data item on stdout.
int   Last(LinkedList_t**, int); //!< LAST - Print last data item on stdout.
int Remove(LinkedList_t**, int); //!< REMOVE nth - Remove nth item from linked list.
int  Clear(LinkedList_t**, int); //!< CLEAR - Release all allocated memory items.
int   Free(LinkedList_t**, int); //!< FREE - Release all allocated memory items.
int   None(LinkedList_t**, int); //!<        For wrong user command.

/****************************************************************************
  PRIVATE MODULE VARIABLES
*****************************************************************************/
static LinkedList_t *pLinkedList = NULL; //!< pointer to linked list structure

static pLinkedListFunction_t apfLinkedList[MAX_USER_COMMAND] =
{
  Exit, //!< Exit function - Finish execution program.
  Put,  //!< Put function - Insert data into linked list.
  Get,  //!< Get function - Get data from nth item into linked list.
  Sort, //!< Sort function - Reorder all data into linked list.
  List, //!< List function - Print on stdout all data.
  First,  //!< First function - Print on stdout the first item of linked list.
  Last,   //!< Last function - Print on stdout the last item of linked list.
  Remove, //!< Remove function - Remove nth item from linked list.
  Clear,  //!< Clear function - Clear (release) all allocated memory used by linked list.
  None    //!< None function - Do nothing, it is used for user command error.
};

/****************************************************************************
  FUNCTION IMPLEMENTATION
*****************************************************************************/

/**
  * @brief Function to parse user command and return and index for each one.
  * @param  pStr           Pointer to user command string.
  * @param  pValue         Pointer to value.
  * @return eUserCommand_t EXIT,PUT,GET,SORT,LIST,FIRST,LAST,REMOVE,CLEAR enumerator for successful,
  *                        otherwise NONE for any error.
  */
eUserCommand_t eGetUserCommandId(char *pStr, int *pValue) 
{
  CHECK_NULL_PTR(pStr, NONE)
  CHECK_NULL_PTR(pValue, NONE)

  // EXIT
  if ( strncmp(pStr, "exit\n", 5) == 0 )
  {
    return EXIT;
  }
  // PUT n
	else if ( strncmp(pStr, "put ", 4) == 0 )
  {
    *pValue = atoi(&pStr[4]);
    return PUT;
  }
  // GET n
	else if ( strncmp(pStr, "get ", 4) == 0 )
  {
    *pValue = atoi(&pStr[4]);
    return GET;
  }
  // SORT
  else if ( strncmp(pStr, "sort\n", 5) == 0 )
  {
    return SORT;
  }
  // LIST
  else if ( strncmp(pStr, "list\n", 5) == 0 )
  {
    return LIST;
  }
  //FIRST
  else if ( strncmp(pStr, "first\n", 6) == 0 )
  {
    return FIRST;
  }
  // LAST
  else if ( strncmp(pStr, "last\n", 5) == 0 )
  {
    return LAST;
  }
  // REMOVE n
	if ( strncmp(pStr, "remove ", 7) == 0 )
  {
    *pValue = atoi(&pStr[7]);
    return REMOVE;
  }
  // CLEAR
  else if ( strncmp(pStr, "clear\n", 6) == 0 )
  {
    return CLEAR;
  }
  
  return NONE;
}

/**
  * @brief Function to run a entry user command.
  * @param pchUserCommand Pointer to string buffer with user command.
  * @return int           0 Successful
  *                       1 Error
  */
int iLinkedListRun(char *pchUserCommand)
{
  CHECK_NULL_PTR(pchUserCommand, 1)

  int iValue = 0;
  //Get ID for use command
  int eCmd = eGetUserCommandId(pchUserCommand, &iValue);

  //Call treater function by command ID.
  return apfLinkedList[eCmd](&pLinkedList, iValue);
}

/**
 *  @brief Function to insert a new item and data into the linked list.
 *  @param ppLinkedList Pointer address of first item of linked list.
 *  @param iValue       Value to be added to the linked list.
 *  @return int         0 Successful
 *                      1 Error
 */
int Put(LinkedList_t** ppLinkedList, int iValue)
{
  CHECK_NULL_PTR(ppLinkedList, 1)

  //Get the last item from the linked list.
  LinkedList_t *item = NULL;

  for (
        item = *ppLinkedList;                     /* get the first item            */
        ((item != NULL) && (item->next != NULL)); /* while it's not the last one   */
        item = item->next                         /* go to next item into the list */
      )
  {
    ; //Run until find the last item into the linked list.
  }

  ///Check empty list and add the firs one
  if ( item == NULL )
  {
    item = (LinkedList_t*)calloc(1, sizeof(LinkedList_t));
    CHECK_NULL_PTR(item, 1)
    *ppLinkedList = item;
  }
  //Otherwise, add a new item to the end of linked list.
  else
  {
    item->next = (LinkedList_t*)calloc(1, sizeof(LinkedList_t));
    CHECK_NULL_PTR(item->next, 1)
    item = item->next;
  }

  //Store data value.
  item->data = iValue;

  return 0; //Successful
}

/**
  * @brief Function to get the n-esimo item from the linked list starting from 1.
  * @param ppLinkedList Pointer address to the first item.
  * @param int          iValue nth item to be gettered.
  * @return int         0 Successful
  *                     1 Error
  */
int Get(LinkedList_t** ppLinkedList, int iValue)
{
  CHECK_NULL_PTR(ppLinkedList, 1)
  CHECK_EQU_INT(iValue, 0, 1)

  int iPos;
  LinkedList_t *item = NULL;

  //Search for specific item.    
  for ( 
        item = *ppLinkedList, iPos = 1;      /* get first item address, load firs item index */
        ((item != NULL) && (iPos < iValue)); /* not NULL and not reached the item            */
        item = item->next, iPos++            /* go to next item, inc position/index counter  */
      )
  {
    ; //just run until reached the item.
  }

  //Not found, return an error.
  CHECK_NULL_PTR(item, 1)
  CHECK_DIFF_INT(iPos, iValue, 1)

  printf("%d\n", item->data);

  return 0; //Successful
}

/**
  * @brief Function to remove the n-esimo item from the linked list starting from 1.
  * @param ppLinkedList Pointer address to the first item.
  * @param iValue       nth item to be removed.
  * @return int         0 Successful
  *                     1 Error
  */
int Remove(LinkedList_t** ppLinkedList, int iValue)
{
  CHECK_NULL_PTR(ppLinkedList, 1)
  CHECK_EQU_INT(iValue, 0, 1)

  int iPos;
  LinkedList_t *pItem = NULL;
  LinkedList_t *pPrevious = NULL;

  //Search for specific item
  for 
  ( 
    pItem = *ppLinkedList, iPos = 1;      /* get first item address, load firs item index */
    ((pItem != NULL) && (iPos < iValue)); /* not NULL and not reached the item            */
    pItem = pItem->next, iPos++           /* go to next item, inc position/index counter  */
  )
  {
    pPrevious = pItem; //store previous item address and run until reached the item.
  }
 
  //Not found, return an error
  CHECK_NULL_PTR(pItem, 1)
  CHECK_DIFF_INT(iPos, iValue, 1)

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
    *ppLinkedList = pItem->next;
    printf("item:%d  value:%d  removed!\n", iPos, pTemp->data);
    free(pTemp);
  }

  //Show all linked list data.
  for ( 
        LinkedList_t *item = *ppLinkedList ;/* get first item address        */
        (item != NULL) ;                    /* while its not a NULL pointer  */
        item = item->next                   /* go to next item into the list */
      )
  {
    //Print data value from the item.
    printf("%d ", item->data);
  }

  //Print a new line at the end of list.
  printf("\n");

  return 0;
}

/**
 *  @brief Function to organize the data order from smaller value to greater values and
 *         print them on the stdout screen after reordered.
 *  @param ppLinkedList Pointer to first item of linked list.
 *  @param iValue       Not used by function.
 *  @return int         0 Successful
 *                      1 Error
 */
int Sort(LinkedList_t** ppLinkedList, int iValue)
{
  UNUSED(iValue)
  CHECK_NULL_PTR(ppLinkedList, 1)

  //Get address of first item from the linked list and follow each item from the list.
  for ( LinkedList_t *actual = *ppLinkedList; actual != NULL ; actual = actual->next)
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
  //Show all linked list data.
  for ( 
        LinkedList_t *item = *ppLinkedList ;/* get first item address        */
        (item != NULL) ;                    /* while its not a NULL pointer  */
        item = item->next                   /* go to next item into the list */
      )
  {
    //Print data value from the item.
    printf("%d ", item->data);
  }

  //Print a new line at the end of list.
  printf("\n");

  return 0;
}

/**
 *  @brief Function to print all elements of a linked list on stdout terminal screen.
 *  @param ppLinkedList Pointer to first item.
 *  @param iValue       Not used by function.
 *  @return int         0 Successful
 *                      1 Error
 */
int List(LinkedList_t** ppLinkedList, int iValue)
{
  UNUSED(iValue)
  CHECK_NULL_PTR(ppLinkedList, 1)

  for ( 
      LinkedList_t *item = *ppLinkedList ; /* get first item address        */
      (item != NULL) ;              /* while its not a NULL pointer  */
      item = item->next             /* go to next item into the list */
    )
  {
    //Print data value from the item.
    printf("%d ", item->data);
  }

  //Print a new line at the end of list.
  printf("\n");

  return 0;
}

/**
 *  @brief Function to print data of first item.
 *  @param ppLinkedList Pointer to first item.
 *  @param iValue       Not used by function.
 *  @return int         0 Successful
 *                      1 Error
 */
int First(LinkedList_t** ppLinkedList, int iValue)
{
  UNUSED(iValue)

  //Check null pointer
  CHECK_NULL_PTR(ppLinkedList, 1)
  //Get firs item address
  LinkedList_t *item = *ppLinkedList;
  //Check null pointer
  CHECK_NULL_PTR(item, 1)
  //Print data
  printf("%d\n", item->data);
  return 0;
}

/**
 *  @brief Function to print last item of linked list on stdout terminal screen.
 *  @param ppLinkedList Pointer to first item.
 *  @param iValue       Not used by function
 *  @return int         0 Successful
 *                      1 Error
 */
int Last(LinkedList_t** ppLinkedList, int iValue)
{
  UNUSED(iValue)
  CHECK_NULL_PTR(ppLinkedList, 1)

  LinkedList_t *item = NULL;

  for (
        item = *ppLinkedList;                            /* get the first item            */
        ((item != NULL) && (item->next != NULL)); /* while it's not the last one   */
        item = item->next                         /* go to next item into the list */
      )
  {
    ; //Run until find the last item into the linked list.
  }

  CHECK_NULL_PTR(item, 1)
  printf("%d\n", item->data);

  return 0;
}

/**
  * @brief Function to release all data on linked list.
  * @param ppLinkedList Pointer to pointer to the first item of linked list.
  * @param iValue       Not used by function
  * @return int         0 Successful
  *                     1 Error
  */
int Clear(LinkedList_t** ppLinkedList, int iValue)
{
  UNUSED(iValue)
  CHECK_NULL_PTR( ppLinkedList, 1)

  Free(ppLinkedList, 0); //Call function to release all allocated memory.
  *ppLinkedList = NULL;//Clear linked list pointer.

  return 0;
}

/**
 *  @brief Function to release previous memory allocation for linked list items.
 *  @param ppLinkedList Pointer to first item of linked list.
 *  @param iValue       Not used by function
 *  @return int         0 Successful
 *                      1 Error
 */
int Free(LinkedList_t** ppLinkedList, int iValue)
{
  UNUSED(iValue)
  CHECK_NULL_PTR(ppLinkedList, 1)

  //Get first item address
  LinkedList_t *item = *ppLinkedList;

  //From the first item until the end, release each one item.
  while (item != NULL)
  {
    LinkedList_t *next = item->next;  //store next item address
    free(item);                       //release memory address of current item
    item = next;                      //go to next item
  }

  return 0;
}

/**
  * @brief Function to treat error or wrong user command.
  * @param ppLinkedList Ignored by function.
  * @param pValue       Ignored by function.
  * @return int         1 Error.
  */
int None(LinkedList_t** ppLinkedList, int iValue)
{
  UNUSED(ppLinkedList)
  UNUSED(iValue)

  return 1;
}

/**
  * @brief Function to treat exit linked list program.
  * @param ppLinkedList Pointer to linked list.
  * @param iValue       Ignored by function.
  * @return int         0 Successful
  *                     1 Error
  */
int Exit(LinkedList_t** ppLinkedList, int iValue)
{
  CHECK_NULL_PTR(ppLinkedList, 1)

  return Free(ppLinkedList, iValue);
}
