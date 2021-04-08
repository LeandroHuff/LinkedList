/**
  @brief Linked List Algorithms
         Read user commands from stdin as:
         PUT n, GET n, LIST, FIRST, LAST, SORT, CLEAR, REMOVE n, EXIT
         and run functions over a linked list according to the user instruction.
         Header file for linked list function implementation.
  @author Leandro Daniel Huff
  @project Developed and Tested on https://replit.com/@LeandroHuff/LinkedList
  @date 2021/04/08 (AAAA/MM/DD)
  @file linkedlist.h
*/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/****************************************************************************
  HEADERS INCLUDES
*****************************************************************************/

/****************************************************************************
  USER TYPEDEFS
*****************************************************************************/
typedef enum en_UserCommand
{
  EXIT = 0,         //!< Exit use command
  PUT,              //!< Put user command
  GET,              //!< Get user command
  SORT,             //!< Sort user command
  LIST,             //!< List user command
  FIRST,            //!< First user command
  LAST,             //!< Last user command
  REMOVE,           //!< Remove user command
  CLEAR,            //!< Clear user command
  NONE,             //!< Not a user command, treat errors.
  MAX_USER_COMMAND  //!< Max user command enumerator
} eUserCommand_t;   //!< User command enumerator type

/****************************************************************************
  PUBLIC VARIABLES
*****************************************************************************/

/****************************************************************************
  PUBLIC FUNCTION
*****************************************************************************/
/**
  * @brief Run a user command passed to function as an index enumerator.
  * @param pchUserCommand User command string.
  * @return int 0 Successful
  *             1 Error
  */
int iLinkedListRun(char *pchUserCommand);

/****************************************************************************
  FUNCTION IMPLEMENTATION
*****************************************************************************/

#endif