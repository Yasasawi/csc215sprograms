/** ***************************************************************************
 * @file
 *
 * @brief   Eric: Constructor/Destructor, Size, FindMax, swapData, sortFreq,
            and printScreen.
 *****************************************************************************/
#include "wordFreq.h"
#include "prog2.h"



 /** **********************************************************************
  * @author Eric Johnson
  *
  * @par Description: 
  * This function is the constructor for the 
  * wordFreqList class. The constructor is called every time an object
  * is created, and head pointer is assigned to null pointer.
  *
  * @returns none

  ************************************************************************/
wordFreqList::wordFreqList()
{
    headptr = nullptr;
}


/** **********************************************************************
  * @author Eric Johnson
  *
  * @par Description: 
  * This function is the destructor for the
  * wordFreqList class. The destructor is called when the object goes out
  * of scope. Each node within the linked list is deleted and the memory
  * is freed.
  *
  * @returns none

  ************************************************************************/
wordFreqList::~wordFreqList()
{
    node* temp;

    while (headptr != nullptr)
    {
        temp = headptr->next;
        delete headptr;
        headptr = temp;
    }

}


/** **********************************************************************
 * @author Eric Johnson
 *
 * @par Description: 
 * The function returns the number of nodes within a linked list by 
 * traversing from headptr to nullptr and incrementing a counter.
 *
 * @returns int - An integer representing the number of nodes within a
 * linked list.
 *
 * @par Example:
 * @verbatim
   
   list.printScreen(); // List contains nodes A, B, C, D

   int nodeCount;
   nodeCount = list.size() // function returns 4 into nodeCount

   @endverbatim

 ************************************************************************/
int wordFreqList::size()
{
    int size = 0;
    node* temp = headptr;

    // While loop travers from headptr to nullptr
    while (temp != nullptr)
    {
        temp = temp->next;
        size++;
    }

    return size;
}


/** **********************************************************************
 * @author Eric Johnson
 *
 * @par Description: 
 * The function travels from headptr until a specified range and will 
 * return the position of the node with the highest frequency. If two 
 * frequencies are equal, the function will return the node which comes 
 * last alphabetically. 
 *
 * @param[in] range - the number of nodes from headptr to search to.
 *
 * @returns int - the position of the node containing the highest
 * frequency (and last alphabetically, if the frequencies are the same).
 *
 * @par Example:
 * @verbatim
   wordFreqlist.list();  // list contains frequency: 1 2 6 1 6 6
                                               word: A A A A B Z
   int position;
   position = list.findMax(5);  // function returns 5 (letter B)

   @endverbatim

 ************************************************************************/
int wordFreqList::findMax(int range)
{
    node* temp = headptr;
    int max = headptr->frequency; // Max frequency assumed at pos 1
    string maxWord = headptr->word; // Max word asuumed at pos 1

    int count = 1;
    int result = 1;

    while (count < range + 1 && temp != nullptr)
    {
        // If new max frequency is found, result is set to count
        if (temp->frequency > max)
        {
            max = temp->frequency;
            maxWord = temp->word;
            result = count;
        }
        // If frequency is equivalent, the word is compared
        else if (temp->frequency == max)
        {
            if (temp->word > maxWord)
            {
                max = temp->frequency;
                maxWord = temp->word;
                result = count;
            }
        }

        // Traverse
        temp = temp->next;
        count++;
    }
    

    return result;
}


/** **********************************************************************
 * @author Eric Johnson
 *
 * @par Description: 
 * The function traverses a linked list and swaps the data contents within
 * two separate nodes. Position 1 is the first node.
 *
 * @param[in] pos1 - The first node's position for swap.
 * @param[in] pos2 - The second node's position for swap.
 *
 * @returns true - swap successful.
 * @returns false - swap did not occur.
 *
 * @par Example:
 * @verbatim
   wordFreqList.list();  // list contains 1, 5, 3, 4, 2
   
   list.swapData(2, 5);  // list is now:  1, 2, 3, 4, 5

   @endverbatim

 ************************************************************************/
bool wordFreqList::swapData(int pos1, int pos2)
{
    node* temp1 = headptr;
    node* temp2 = headptr;
    int count1 = 1;
    int count2 = 1;

    // No swaps if two of the same node is selected
    if (pos1 == pos2)
        return false;

    // Traversing first pointer
    while (count1 < pos1 && temp1->next != nullptr)
    {
        temp1 = temp1->next;
        count1++;
    }

    // Traversing second pointer
    while (count2 < pos2 && temp2->next != nullptr)
    {
        temp2 = temp2->next;
        count2++;
    }

    // Swapping Frequency
    int freq1 = temp1->frequency;
    temp1->frequency = temp2->frequency;
    temp2->frequency = freq1;

    // Swapping Words
    string word1 = temp1->word;
    temp1->word = temp2->word;
    temp2->word = word1;

    return true;
}


/** **********************************************************************
 * @author Eric Johnson
 *
 * @par Description: 
 * This function sorts a linked list in order of frequency. If more than 
 * one node has the same frequencies, the node is then sorted 
 * alphabetically. 
 * 
 * @returns none
 *
 * @par Example:
 * @verbatim
   wordFreqList.list(); // list contains frequency: 1 2 6 1 6 6
                                              word: A A A A B Z

   list.sortFreq();     // list is now   frequency: 1 1 2 6 6 6
                                              word: A A A A B Z
   @endverbatim

 ************************************************************************/
void wordFreqList::sortFreq()
{   
    int listSize = size();
    int posMax;

    while (listSize > 0)
    {
        posMax = findMax(listSize);
        swapData(listSize, posMax);

        listSize--; // Max placed at end of list per pass through
    }
}


/** **********************************************************************
 * @author Eric Johnson
 *
 * @par Description: 
 * This function prints the linked list to the output stream for debugging
 * purposes.
 *
 * @returns none
 ************************************************************************/
void wordFreqList::printScreen()
{
    node* temp = headptr;
    int i = 1;

    while (temp != nullptr)
    {
        cout << i << ": " << temp->word << " " << temp->frequency << " " <<
            temp->word.length() << endl;
        temp = temp->next;
        i++;
    }
}
