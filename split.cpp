/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE

  // Base Case: Check If List Is Empty. If so, return nothing.
  if ( in == nullptr ) {
    return; // return nothing since the list is empty
  }

  Node* temp = in; // temp node to store the current node
  in = in->next; // Moves in to the next node in the list

  // if statement to check if node contains an even variable
  if (temp->value % 2 == 0) {
      temp->next = evens; // The node is now linked to head of evens 
      evens = temp; // Update head of evens list to temp
  }
  // if statement to check if node contains an odd variable
  if (temp->value % 2 == 1) {
      temp->next = odds; // The node is now linked to head of odds
      odds = temp; // Update head of odds list to temp
  }
  // Recursion to next part of the list
  split ( in, odds, evens);
}

/* If you needed a helper function, write it here */
