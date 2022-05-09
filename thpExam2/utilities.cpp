/** ***************************************************************************
 * @file
 *
 * @brief    functions not needed in class declaration.
 * puncuation and file input and output.
 *****************************************************************************/
#include "wordFreq.h"
#include "prog2.h"

 /** **********************************************************************
  *  @author Yasas Wijesekara
  *
  *  @par Description
  *  closes all the files
  *
  *  @param[in] fin the file to be closed
  *  @param[in] fout the file to be closed
  *  @param[in] foutTwo the file to be closed
  *
  *  @returns none
  *
  *  @par Example
  *  @verbatim
     ifstream fin;
     ofstream fout;
     ofstream foutTwo;

     cleanUp(fin, fout, foutTwo);//the files are closed

     @endverbatim
  ************************************************************************/
void cleanUp(ifstream& fin, ofstream& fout, ofstream& foutTwo)
{
    if (fout.is_open() == true)
    {
        fout.close();
    }
    if (foutTwo.is_open() == true)
    {
        foutTwo.close();
    }
    if (fin.is_open() == true)
    {
        fin.close();
    }
    exit(0);
}

/** *********************************************************************
 * @author Grant Blasing
 *
 * @par Description:
 * checks the list for a word
 *
 * @param[in] fin - stream for input.
 * @param[in] inputFile - file to open.
 *
 * @returns bool based on success or failure
 *
 * @par Example:
   @verbatim

   ifstream fin;
   openFiles(fin, inputFile);

   output: file is opened;
   @endverbatim

 ***********************************************************************/
bool openFiles(ifstream& fin, string inputFile)
{
    fin.open(inputFile); //open
    if (!fin.is_open())
    {
        cout << "Unable to open: " << inputFile; // message
        return false;
    }
    return true;
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * checks the list for a word
 *
 * @param[in] fout - stream for output.
 * @param[in] outputFile - file to open.
 *
 * @returns bool based on success or failure
 *
 * @par Example:
   @verbatim
   string outputFile;
   ofstream fout;
   openFiles(fout, outputFile);

   output: file is opened;
   @endverbatim

 ***********************************************************************/
bool openFilesOutput(ofstream& fout, string outputFile)
{
    fout.open(outputFile);
    if (!fout.is_open())
    {
        cout << "Unable to open: " << outputFile;
        return false;
    }
    return true;
}


/** *********************************************************************
 * @author Grant Blasing
 *
 * @par Description:
 * This takes a word sets all characters to lowercase and removes all
 * punctuation.
 *
 * @param[in] word - string to be formatted
 *
 * @returns bool - true for success false for failure.
 *
 * @par Example:
   @verbatim
   string word = "##YoU'VE@@#";
   findWord(word);

   
   output: true; // word = "you've"
   @endverbatim

 ***********************************************************************/
bool findWord(string& word)
{
    int i = 0;
    size_t size = word.size();
    bool alpha = false;
    while (i < size) 
    {
        if (ispunct(word[i])) // is char punct
        {
            if (i > 0 && i < size)
            {
                if (isalpha(word[i - 1]) != 0 && isalpha(word[i + 1]))
                {
                    alpha = true;
                }
            }
            if (alpha == false)
            {
                word.erase(i--, 1); // remove punct but only when not in the
                size = word.size(); // word
            }
        }
        i++;
    }
    i = 0;
    for (i = 0; i < word.size(); i++) //whole string to tolower
    {
        word[i] = tolower(word[i]);
    }
    return true;
}