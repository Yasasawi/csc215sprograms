/** *********************************************************************
 * @file
 *
 * @brief takes a .txt of a strings removes punctuation and inserts into 
 * a linked list then prints the list into a .txt file based on frequency 
 * of the word or length of the word.
 ***********************************************************************/


 /** ********************************************************************
 *
 * @mainpage thpExam2 - Word Frequency
 *
 * @section course_section Course Information
 *
 * @authors Grant Blasing, Yasas Wijesekara, Eric Johnson.
 *
 * @date March 4, 2022
 *
 * @par Instructor:
 *         Professor Schrader
 *
 * @par Course:
 *         CSC 215 - M01 - 9:00 am
 *
 * @par Location:
 *         Classroom Buliding - Room 329
 *
 * @section program_section Program Information
 *
 * @details 
 * The program will read a given input file from the command line 
 * arguments and perfrom one of four operations; -f, -l, -fl, or -lf. 
 * The program will then read each word from a given input file into 
 * a linked list while checking and ignoring duplicate words, 
 * removing punctuation, and converting all words into lower case. The
 *  program will then output the compiled information into two output 
 * files provided in the command line arguments. One file will contain 
 * every word in alphabetical order, while the other will output either 
 * each word's frequency statistics or length statistcs, or both, depending 
 * on the command line arguments.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      use the following key
 *          Usage: inputfile.txt wordData.txt stats.txt --option
 *
 * --option Types (-l, -f, -fl, -lf)
 *
 * stats.txt (name of output file)
 *
 * inputFile.txt (name of input file)
 *
 * wordData.txt (output the linked list)
 *
 * @par Usage: inputfile.txt wordData.txt stats.txt --option
   @verbatim
   c:\> thpExam2.exe  inputfile.txt wordData.txt stats.txt --option
   d:\> c:\bin\thpExam2.exe shortstory.txt wordData.txt stats.txt -f

        inputfile.txt - file contains strings to be sorted.
        wordData.txt - file for output of linked list.
        stats.txt - file for output of option.
        --option - option for output by frequency or length.
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  none
 *
 * @todo Finish documenting with doxygen tags
 *
 * @par Modifications and Development Timeline:
   @verbatim
   Date          Modification
   ------------  --------------------------------------------------------
   Mar   4, 2022  Setup our files.
   Mar  11, 2022  finished class declaration.
   Mar  18, 2022  Wrote file input.
   Mar  25, 2022  Wrote insert, count,findWord and output functions.
   Apr   1, 2022  wrote sorts.
   Apr   2, 2022  finishing main and doxygen.
   Apr   4, 2022  more doxygen.
   @endverbatim

   Gitlab commit log, <a href = 
   "https://gitlab.cse.sdsmt.edu/csc215/spring2022/team06/-/commits/master"
   target="_blank">
   Click Here.</a>
 *
 ***********************************************************************/
#include "wordFreq.h"
#include "prog2.h"

 /** *********************************************************************
  * @author Grant Blasing, Yasas Wijesekara, Eric Johnson.
  *
  * @par Description:
  * This is the starting point to the program.  The function will read a
  * given input file from the command line arguments and perfrom one of
  * four operations; -f, -l, -fl, or -lf. The function will then read each
  * word from a given input file into a linked list while checking
  * and ignoring duplicate words, removing punctuation, and converting
  * all words into lower case. The function will then output the compiled
  * information into two output files provided in the command line
  * arguments. One file will contain every word in alphabetical order, 
  * while the other will output either each word's frequency statistics or
  * length statistcs, or both, depending on the command line arguments.
  * 
  *
  * @param[in] argc - the number of arguments from the command prompt.
  * @param[in] argv - Usage: inputfile.txt wordData.txt stats.txt --option
  *
  * @returns 1 if command line arguments are not valid.
  * @returns 2 if files failed to open.
  * @returns 0 all succeeded
  *
  * @verbatim
    see usage statement above.
    @endverbatim
  *
  ***********************************************************************/
int main(int argc, char** argv)
{
    wordFreqList list;
    string inputFile;
    string outputFile;
    string statsFile;
    string option;
    string x;
    ifstream fin;
    ofstream foutStats;
    ofstream foutWords;

    //accessing the files and checking if they opened/exist
    if (argc == 5)
    {
        inputFile = argv[1];
        outputFile = argv[2];
        statsFile = argv[3];
        option = argv[4];
    }
    else if(argc == 4)
    {
        inputFile = argv[1];
        outputFile = argv[2];
        statsFile = argv[3];
        option = "-f";
    }
    else
    {         //usage statement
        cout << "Usage: textFile.txt dataFile statsFile outputType" << endl; 
        cleanUp(fin, foutWords, foutStats);
        return 1;
    }
    openFilesOutput(foutWords, outputFile); //opening for input and output
    openFilesOutput(foutStats, statsFile);
    openFiles(fin, inputFile);
    while (fin >> x)
    {
        findWord(x);
        if(list.checkList(x)) //checks for duplicates, inserts, and increments.
            list.insert(x);
        list.count(x);
    }
    list.printAlpha(foutWords);
    if (option == "-f")// output options.
    {
        list.printFrequency(foutStats);
    }
    if (option == "-l")
    {
        list.printLength(foutStats);
    }
    if (option == "-fl")
    {
        list.printFrequency(foutStats);
        list.printLength(foutStats);
    }
    if (option == "-lf")
    {
        list.printFrequency(foutStats);
        list.printLength(foutStats);
    }
    cleanUp(fin, foutStats, foutWords);
    return 0;
}