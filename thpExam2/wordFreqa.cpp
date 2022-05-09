/** ***************************************************************************
 * @file
 *
 * @brief   Grant: insert, count, and checkList for duplicates.
 *****************************************************************************/
#include "wordFreq.h"
#include "prog2.h"

 /** *********************************************************************
 * @author Grant Blasing
 *
 * @par Description:
 * inserts a word into a linked list alphabetically.
 *
 * @param[in,out] word - string to be passed into list.
 *
 * @returns bool bases on success of insertion.
 *
 * @par Example:
   @verbatim

   string word = "bad";
   wordFreqList list;

   list.insert(word);

   cout << list << endl;

   output: bad;
   @endverbatim

 ***********************************************************************/
bool wordFreqList::insert(string& word)
{
    node* temp = headptr;
    node* newWord = new node;
    node* temp1;
    int i = 0;
    temp1 = headptr;
    newWord->next = nullptr;
    newWord->word = word;

    if (headptr == nullptr)
    {
        headptr = newWord;
        newWord->next = nullptr;
        return true;
    }
    while (temp != nullptr)
    {
        if (newWord->word < temp->word)
        {
            if (temp1 == temp) // checking for location in the list before insert.
            {
                headptr = newWord;
                newWord->next = temp;// inserts and  moves on to next.
                return true;
            }
            else // not at the beginning just insert.
            {
                temp1->next = newWord;
                newWord->next = temp;
                return true;
            }
        }
        if (temp->next == nullptr)// at the end insert.
        {
            temp->next = newWord;
            newWord->next = nullptr;
            return true;
        }
        temp1 = temp;
        temp = temp->next; // next word.
    }
    return false;
}


/** *********************************************************************
 * @author Grant Blasing
 *
 * @par Description:
 * counts the frequency of words in a linked list and uses a variable to
 * store it in the linked list.
 *
 * @param[in,out] word - string to locate word.
 *
 * @returns bool bases on success of counting.
 *
 * @par Example:
   @verbatim

   string word = "bad";
   wordFreqList list;

   list.count(word);

   cout << temp -> frequency << endl;

   output: 1;
   @endverbatim

 ***********************************************************************/
bool wordFreqList::count(string word)
{
    node* temp = nullptr;
    temp = headptr;

    while (temp != nullptr) //runs through the list
    {
        if (temp->word == word)// find word
        {
            temp->frequency = temp->frequency + 1;// count
            return true;
        }
        temp = temp->next; // next word
    }
    return false;
}


/** *********************************************************************
 * @author Grant Blasing
 *
 * @par Description:
 * checks the list for a word
 *
 * @param[in,out] word - structure containing the string to look for.
 *
 * @returns bool bases on success of locating the word.
 *
 * @par Example:
   @verbatim

   string word = "bad";
   wordFreqList list;
   list.insert(word);
   list.checkList(word);

   output: true;
   @endverbatim

 ***********************************************************************/
bool wordFreqList::checkList(string word)
{
    node* temp = nullptr;
    temp = headptr;

    while (temp != nullptr) // checks list
    {
        if (temp->word == word) // finds word
        {
            return false; // false so dont insert if it already exists
        }
        temp = temp->next;// next item
    }
    return true;
}




