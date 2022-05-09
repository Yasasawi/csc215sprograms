/** ***************************************************************************
 * @file
 *
 * @brief   Yasas: Prints and formatting for frequency, length and alphabetically printing also a sort for frequency
 *****************************************************************************/
#include "wordFreq.h"
#include "prog2.h"
 /** *********************************************************************
  * @author Yasas Wijesekara
  *
  * @par Description:
  * This function formats and prints all of the sorted frequencies
  *
  * @param[in] ostream - the data output file for the outputs to be sent to
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    ostream foutStats;
    wordFreqList list;
    list.sortFreq();

    list.printFrequency(foutStats); //prints and formats all of the frequency data in the output file

    @endverbatim

  ***********************************************************************/
void wordFreqList::printFrequency(ostream& ostream) const// prints data if -f is specified in command line.
{
    node* temp = headptr;
    node* temp1 = headptr;
    int max = 0;
    int i = 0, j = 0;
    int count = 0;
    while (temp != nullptr)
    {
        if (temp->frequency > max) //find the max frequency
        {
            max = temp->frequency;
        }
        temp = temp->next;
    }

    for (i = max; i > 0; i--)
    {
        temp = headptr;
        temp1 = headptr;
        count = 0;
        while (temp != nullptr)
        {
            if (i == temp->frequency && count == 0) //if the frequency exists print the header 
            {
                ostream << "*********************************************************" << endl;
                ostream << "* " << "Frequency " << i << endl;
                ostream << "*********************************************************" << endl;
                while (temp1 != nullptr)
                {
                    if (temp1->frequency == i) //printing all relavent words with that frequency
                    {
                        if (j % 3 == 0 && j != 0) //formatting for 3 words per line
                        {
                            ostream << endl;
                        }
                        ostream << setw(17) << left << temp1->word;
                        j++;
                    }
                    temp1 = temp1->next;
                }
                j = 0; //reset counter 
                ostream << endl << endl;
                count++;
            }
            temp = temp->next; //increment to next node
        }
    }
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function formats and prints all of the lengths
 *
 * @param[in] ostream - the data output file for the outputs to be sent to
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ostream foutStats;
   wordFreqList list;
   list.sortLength();

   list.printLength(foutStats); //prints and formats all of the length data in the output file

   @endverbatim

 ***********************************************************************/
void wordFreqList::printLength(ostream& ostream) const//prints data if -l is specified in command line.
{
    node* temp = headptr;
    node* temp1 = headptr;
    size_t max = 0;
    size_t i = 0, j = 0;
    int count = 0;
    while (temp != nullptr)
    {
        if (temp->word.size() > max) //finding the max length
        {
            max = temp->word.size();
        }
        temp = temp->next;
    }

    for (i = max; i > 0; i--)
    {
        temp = headptr;
        temp1 = headptr;
        count = 0;
        while (temp != nullptr)
        {
            if (i == temp->word.size() && count == 0) //if the length exists print the header
            {
                ostream << "*********************************************************" << endl;
                ostream << "* " << "length of " << i << endl;
                ostream << "*********************************************************" << endl;
                while (temp1 != nullptr)
                {
                    if (temp1->word.size() == i)
                    {
                        if (j % 3 == 0 && j != 0) //formatting 3 words per line
                        {
                            ostream << endl;
                        }
                        ostream << setw(17) << left << temp1->word;
                        j++;
                    }
                    temp1 = temp1->next;
                }
                j = 0; //reset formatting counter to 0
                ostream << endl << endl;
                count++;
            }
            temp = temp->next; //increment to next node
        }
    }
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function formats and prints all of the data alphabetically
 *
 * @param[in] ostream - the data output file for the outputs to be sent to
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   ostream foutWords;
   wordFreqList list;

   list.printAlpha(foutWords); //prints and formats all of the alphabet data in the output file

   @endverbatim

 ***********************************************************************/
void wordFreqList::printAlpha(ostream& ostream) const
{
    wordFreqList list;
    string firstLetter;
    node* lengthTemp = headptr;
    node* temp = headptr;
    int i = 0;
    //iterate through list
    while (temp->next != nullptr)
    {
        //check first letter of the word 
        firstLetter = (temp->word).substr(0, 1);
        //if statement that check if the current first letter doesnt equal the second to avoid duplicates
        if (firstLetter != (temp->next->word).substr(0, 1))
        {
            ostream << "*********************************************************" << endl;
            ostream << "* " << "words starting with " << temp->word.substr(0, 1) << endl;
            ostream << "*********************************************************" << endl;
            while (lengthTemp != nullptr) //prints all words that start with the same letter
            {
                if ((lengthTemp->word).substr(0, 1) == temp->word.substr(0, 1))
                {
                    if (i % 3 == 0 && i != 0) //this if statement just ensures theres 3 items per line
                    {
                        ostream << endl;
                    }
                    ostream << setw(17) << left << lengthTemp->word;
                    i++;
                }
                lengthTemp = lengthTemp->next;
            }
            ostream << endl;
            temp = temp->next;
            lengthTemp = headptr; //reset i to 0 and the temp node variable for the data to headptr
            i = 0;
        }
        else
        {
            temp = temp->next; //goes to the next letter if its a duplicate
        }
    }
}