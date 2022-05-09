/** *********************************************************************
 * @file
 *
 * @brief  Prototypes for utilities.cpp
 ***********************************************************************/
#pragma once
#include "prog2.h"

#ifndef __WORDFREQ_H
#define __WORDFREQ_H
 /** **********************************************************************
  *  @class wordFreqList
  *  @brief This class constructs a linked list and functions to modify it.
 ************************************************************************/
class wordFreqList
{
    public:
/************************************************************************
 *                         Function Prototypes
 ***********************************************************************/
        wordFreqList(); // headptr = nullptr
        ~wordFreqList(); //remove all nodes set ptr to null
        bool insert(string &word);  // inserts the word into the linked list
        bool checkList(string word); // checks list for word.
        bool count(string word);  //increments the counter for frequency and checks for duplicates.
        void printFrequency(ostream& ostream) const; // prints data if -f is specified in command line.
        void printLength(ostream& ostream) const; //prints data if -l is specified in command line.
        void printAlpha(ostream& ostream) const;
        void sortFreq();  // Sorts a linked list by frequency
        void printScreen(); // For debugging - prints to screen.
        int size(); // returns size of linked list
        int findMax(int range); // returns the order of the largest item within a range
        bool swapData(int pos1, int pos2); // Swaps data within two nodes given their positions. Returns true if succesful.
    private:
/** **********************************************************************
 *  @struct wordFreqList::node
 *  @brief This structure is used to hold data and pointers to search 
 *  through the list.
************************************************************************/
        struct node
        {
/** **********************************************************************
* @brief word string to hold words in the list.
************************************************************************/
            string word;
/** **********************************************************************
* @brief frequency int to hold the number of times the word appears in
* the .txt.
************************************************************************/
            int frequency = 0;
/** **********************************************************************
* @brief next node to point to the next item in the linked list.
************************************************************************/
            node* next;
        };
/** **********************************************************************
* @brief headptr node that always points to the start of the list.
************************************************************************/
        node* headptr;
};
#endif