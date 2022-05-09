/** **************************************************************************
 * @file
 *
 *  @brief contains the main function
 *
 *  Author: Yasas Wijesekara
 ****************************************************************************/
 /** **************************************************************************
  * @mainpage Program 3 - Knights Tour
  *
  * @section course_section Course Information
  *
  * @author Yasas Wijesekara
  *
  * @par Professor:
  *         Dr. Roger L Schrader
  *
  * @par Course:
  *         CSC215 - M01 - Proggramming Techniques
  *
  * @par Location:
  *         McLaury - 330
  *
  * @date Due April 25, 2022
  *
  * @section program_section Program Information
  *
  * @details
  * This program utilizes backtracking to find the first path that a knight
  * can take throughout a specified chess board
  *
  * There are two options to using this program.
  *
  * The first option is run through not specifing a input or output
  * it creates a menu giving you options to change the size
  * or the starting postiion of the knight
  *
  * The second option is for a specified file and gives all of the permutations
  * for the file based off a given size and starting position
  * 
  * both options have error checking for an invalid size and coord
  *
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      the menu option is for just running the exe 
  *      if two files are given 
  *      it is required to have them as a .pz file, and .tours file
  *
  * @par Usage:
    @verbatim
    c:\> prog3.exe input_file.pz output_file.tours
             inputfile  - filename containing size of grid and coordinates
             outputfile - filename to write our data to
    @endverbatim
  *
  *
  * @par Modifications and Development Timeline:
  * This is a link to gitlab's commit as an example. To view <a target="_blank"
  * href="https://gitlab.cse.sdsmt.edu/101083339/csc215s22programs">click here.</a>
  *
  *****************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <sstream>

using namespace std;
/** ***************************************************************************
 *                         Function Prototypes
******************************************************************************/
void createMenu(int**& pos, int**& sol, int* loc, int& size, char option);
bool setup(int**& pos, int**& sol, int size);
void menuOutput(int* location, int size);
bool arrAlloc(int**& array, int size);
void free2d(int**& doubleArray, int size);
bool createBoard(int**& pos, int size);
bool solSetup(int**& sol, int size);
void printTour(int** sol, int size, int* loc, int tour, ostream& type);
bool knightsTour(int**& pos, int** sol, int size, int num, int x, int y, 
    int**& newSol);
bool isSafe(int** sol, int size);
void fileRead( ifstream& fin,  ofstream& fout, int size, int* in);
void cleanUp(ifstream& fin, ofstream& fout);
/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This is the main function. Here we start and end our program. first we
 * check our arguments if no arguments, we give the user a menu to run the
 * program with. 
 *
 * @param[in]     argc - the number of arguments
 * @param[in]    argv - our files
 *
 * @returns 0 and exits program.
 *
 *****************************************************************************/
int main(int argc, char** argv)
{
    // start up initialization. 
    int** pos = nullptr;
    int** sol = nullptr;

    int loc[2] = { 7, 7 }; //just the starting coordinate
    int size = 8; //starting size
    char choice = 0;

    ifstream fin;
    ofstream fout;
    
    string inputFile, outputFile; 


    //the default option for when a file is not specifed 
    //runs the permutation through the command line
    if (argc == 1)
    {

        //error checking for the dynamic arrays
        if (!arrAlloc(pos, size + 4))
        {
            cout << "Memory failed To Allocate" << endl;
            return 0;
        }
        if (!arrAlloc(sol, size))
        {
            cout << "Memory failed to allocate" << endl;
            return 0;
        }

        //setting up the board here
        createBoard(pos, size);
        solSetup(sol, size);

        pos[9][9] = -1; // filling the first spot
        sol[7][7] = 1;

        //runs the menu function
        createMenu(pos, sol, loc, size, choice);
    }
    else if (argc == 3) //When a file is specified
    {
        //opens up the two files for input and output
        //the output file is set to append to the end
        inputFile = argv[1];
        outputFile = argv[2]; 
        fin.open(inputFile);
        if (!fin.is_open())
        {
            cout << "File " << inputFile << " could not open." << endl;
            cleanUp(fin, fout);
            return 0;
        }
        fout.open(outputFile, ios::app);
        if (!fout.is_open())
        {
            cout << "File " << outputFile << " could not open." << endl;
            cleanUp(fin, fout);
            return 0;
        }

        fileRead(fin, fout, size, loc); //runs the permuation with the given file inputs
    }
    else
    {
        cout << "Usage: prog3.exe inputfile outputfile" << endl;
        return 0;
    }


    cleanUp(fin, fout);

    //freeing up the memory
    free2d(pos, size + 4);
    free2d(sol, size);

    return 0; 
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function is for when a file is specified, it just runs the permutation
 * as well as cleans up any memory and handles the file, it also reads the data 
 * given from the file. 
 *
 * @param[in, out]    fin - The input file
 * @param[in, out]    fout - The output file
 * @param[in]         size - the size of the board
 * @param[in]         in - the two coordiantes
 *
 * @returns none
 *
 *****************************************************************************/
void fileRead( ifstream& fin,  ofstream& fout, int size, int* in)
{
    int** pos = nullptr;
    int** newSol = nullptr;
    int** sol = nullptr;
    int i = 1;

    //while loop for when a file is specified
    while (fin >> size)
    {
        // input for locations
        fin >> in[0];
        fin >> in[1];

        //memory error checking
        if (!arrAlloc(pos, size + 4))
        {
            cout << "Memory Failed To Allocate" << endl;
            return;
        }
        if (!arrAlloc(sol, size))
        {
            cout << "Memory Failed To Allocate" << endl;
            return;
        }

        //making the solution and board
        createBoard(pos, size);
        solSetup(sol, size);

        sol[in[0]][in[0]] = 1;

        if (!arrAlloc(newSol, size))
        {
            cout << "Memory Failed To Allocate" << endl;
            return;
        }
        //making the solution array
        solSetup(newSol, size);

        //running the backtracking knights tour function here 
        knightsTour(pos, newSol, size, 1, in[0], in[1], sol);

        //printing out the first tour
        printTour(sol, size, in, i, fout);

        i++;

        fout << endl;

        //freeing up the memory and the arrays
        free2d(sol, size);
        free2d(newSol, size);
        free2d(pos, size + 4);
    }
    //freeing up the memory and the arrays
    free2d(sol, size);
    free2d(newSol, size);
    free2d(pos, size + 4);
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function is the menu function, based upon the selection of 1, 2, or 3
 * the menu will execute a function.
 *
 * Option 1 is just to change the board size
 *
 * Option 2 is just for changing the board's starting coordinates
 *
 * Option 3 is just to call the knights tour function and run the program
 *
 * If an input is not a 1, 2, or a 3 the program will output error and
 * call menu once again.
 *
 * @param[in, out]     pos - this is our 2D allocated array for bound checking
 * @param[in, out]     sol - This is our final output allocated array
 * @param[in]          loc - this is a 1D array of our two corrdinates
 * @param[in, out]     size - this is the size of our Board
 * @param[in]          option - this is the last selected choice.
 *
 * @returns none
 *
 *****************************************************************************/
void createMenu(int**& pos, int**& sol, int* loc, int& size, char option)
{
    int newSize;
    int start = 0;
    int newLoc[2];
    int** newSol = nullptr;

    menuOutput(loc, size);

    //getting the choice from the menu
    cin >> option;
    cout << endl;

    //for choice 1
    if (option == '1')
    {
        cout << "Enter the size of the NxN Board (>3): ";
        cin >> newSize;

        if (newSize - 1 < loc[0] || newSize - 1 < loc[1] || newSize < 4) //checking with the coordinates to make sure the new size fits 
        {
            //error message for an invalid board
            cout << "Invalid Board size" << endl << endl;
            createMenu(pos, sol, loc, size, option);
        }
        else
        {
            //set up the board to the new size and check allocation.
            size = newSize; 
            setup(pos, sol, size);
            sol[loc[0]][loc[1]] = 1;
            cout << endl;
            createMenu(pos, sol, loc, size, option);
        }
    }

    //for choice 2
    else if (option == '2')
    {
        cout << "Enter Starting Coordinates [ row, col ]: ";
        cin >> newLoc[0] >> newLoc[1];

        //for an invalid coord
        if (newLoc[0] > size - 1 || newLoc[1] > size - 1 || newLoc[0] < 0 || 
            newLoc[1] < 0)
        {
            cout << "Change Your Starting Location to a valid position" 
                << endl << endl; 

            createMenu(pos, sol, loc, size, option);
        }
        // if coodinate is not right size error and call menu
        else
        {
            //if its a valid coord we mark it on the solution array
            sol[loc[0]][loc[1]] = 0;
            loc = newLoc;
            sol[loc[0]][loc[1]] = 1;
            cout << endl;
            createMenu(pos, sol, loc, size, option);
        }
    }

    //for choice 3
    else if (option == '3')
    {
        // choice number three is solving the tour
        pos[loc[0] + 2][loc[1] + 2] = -1;

        // check if allocation failed
        if (!arrAlloc(newSol, size))
        {
            cout << "memory was unable to allocate" << endl;
            return;
        }

        //makes a solution board to match later on
        solSetup(newSol, size);

        // solve the tour using the knights tour backtracking function
        knightsTour(pos, newSol, size, 1, loc[0], loc[1], sol);
    
        //only prints the first tour
        printTour(sol, size, loc, 1, cout);
       
        // cleaning our memory
        free2d(newSol, size);

        return;
        // exit the menu and returns to main.
    }
    else
    {
        // if a choice that wasn't supposed to happen the error
        // message is sent and the menu is recalled.
        cout << "Invalid Option, Please Enter a 1, 2, or 3" << endl << endl;
        createMenu(pos, sol, loc, size, option);
    }

}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function prints out the begining of the menu
 *
 * @param[in]          loc - this is our location corrdinates
 * @param[in]          size - this is the size of the board
 *
 * @returns none
 *
 *****************************************************************************/
void menuOutput(int* loc, int size) //literally just outputs the menu items
{
    //some output statements for making the menu
    cout << "   " << setw(3) << "1) Change Board Size from " << size << "x" 
        << size << endl;
    cout << "   " << setw(3) << "2) Change starting location from [" << loc[0] 
        << "," << loc[1] << "]" << endl;
    cout << "   " << setw(3) << "3) Exit and Solve Tour" << endl;
    cout << "Enter Choice: ";
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function allocates does our setup that is called in our menu
 * when the size changes.
 *
 * @param[in, out]     pos - this is the postition of the board
 * @param[in, out]     sol - this will be the solution later on
 * @param[in]          size - this is the board
 *
 * @returns true if done successfully
 * @returns false if error in allocation.
 *
 *****************************************************************************/
bool setup(int**& pos, int**& sol, int size) //just makes the board pretty much
{
    if (!arrAlloc(pos, size + 4))
    {
        cout << "memory was unable to allocate" << endl;
        return false;
    }
    if (!arrAlloc(sol, size))
    {
        cout << "memory was unable to allocate" << endl;
        return false;
    }

    //runs both of the setup functions
    createBoard(pos, size);
    solSetup(sol, size);

    return true;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function allocates any typename 2D array and returns it based upon
 * the size of the array.
 *
 * @param[in, out]     arr - this is the array that will be allocated.
 * @param[in]          size - this is the desisred size of the 2D array.
 *
 * @returns true if done successfully
 * @returns false if error in allocation.
 *
 *****************************************************************************/

bool arrAlloc(int**& arr, int size)
{
    int i = 0;
    //makes the array
    arr = new(nothrow) int * [size]; //making a 1d ptr array
    if (arr == nullptr)
    {
        arr = nullptr;
        return false;
        //allocation failed
    }
    for (i = 0; i < size; i++)//aking a ptr array at every spot in the 1d array
    {
        arr[i] = new(nothrow) int[size];
        if (arr[i] == nullptr)
        {
            free2d(arr, size); //error checking
            return false;
        }
    }
    return true;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function cleans/deletes any typename 2D array and returns the 2D
 * array as empty.
 *
 * @param[in, out]     arr - this is the array that will be cleaned
 * @param[in]          size - this is the size of the array
 *
 * @returns none
 *
 *****************************************************************************/
void free2d(int**& arr, int size)
{
    int i = 0;

    for (i = 0; i < size; i++)
    {
        delete[] arr[i];
    }

    delete[] arr;

    // deleting the 2D array.
    arr = nullptr;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function fills the pos array with 0's and -1's. the outer two
 * layers are filled with -1's for bound checking, while the inside is
 * filled with 0's
 *
 * @param[in, out]     pos - this is the array that will be filled
 * @param[in]          size - this is the size of the board.
 *
 * @returns true if done successfully
 * @returns false size is 0
 *
 *****************************************************************************/
bool createBoard(int**& pos, int size)
{
    int i, j;

    if (size == 0)
    {
        return false; //checking for an empty board
    }

    //these two for loops make two borders of -1 around the board
    for (i = 0; i < size + 4; i++)
    {
        pos[0][i] = -1; //making a border of negative 1 for the array sides
        pos[1][i] = -1;
        pos[size + 2][i] = -1;
        pos[size + 3][i] = -1;
    }

    for (i = 0; i < size + 4; i++)
    {
        pos[i][0] = -1; //making a border of negative 1 for the array top bound
        pos[i][1] = -1;
        pos[i][size + 2] = -1;
        pos[i][size + 3] = -1;
    }

    for (i = 2; i < size + 2; i++)
    {
        for (j = 2; j < size + 2; j++)
        {
            pos[i][j] = 0; //making the board inside of the bounds 
                           //making it all 0's
        }
    }

    return true;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function fills any typename 2D array and returns it based upon
 * the size of the array. the 2D array is filled completly with 0.
 *
 * @param[in, out]     sol - this is the array that will be filled.
 * @param[in]          size - this is the size of the 2D array.
 *
 * @returns true if done successfully
 * @returns false if size is less than 3
 *
 *****************************************************************************/
bool solSetup(int**& sol, int size)
{
    int i, j;

    //makes sure the array is fufilling the bound set by the menu which is that
    //the size needs to be less than three
    if (size < 3)
    {
        return false;
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            sol[i][j] = 0; //setting all values inside to 0
        }
    }

    return true;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function is just the knights tour function that does the 
 * recursion for finding all of the spots that a knight can go on a 
 * board.
 *
 * @param[in, out]     pos - This is our position check for bounds.
 * @param[in]          sol - this is our check solution
 * @param[in]          size - this is the size of the board
 * @param[in]          num - this is the number of moves made
 * @param[in]          x - this is our x coordinate
 * @param[in]          y - this is our y coordinate
 * @param[in, out]     newSol - this is our final solution array.
 *
 * @returns true if done successfully
 * @returns false if the solution has not been found yet
 *
 *****************************************************************************/
bool knightsTour(int**& pos, int** sol, int size, int num, int x,
    int y, int**& newSol)
{
    //2d array of all of the knights moves
    int knight[8][2] = { {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, 
        {-1, -2}, {-2, -1} };

    int xPos;
    int yPos;
    int i;
    int j;

    pos[x + 2][y + 2] = -1; //sets the spot to a -1 to make sure it doesnt get used
    sol[x][y] = num; //set the spot to make sure its filled 
    //basecase for the permuation, essentailly is checking for if that spot is a solution
    while (num == size * size) //checks if all the spots are filled
    {
        for (i = 0; i < size; i++)
        {
            for (j = 0; j < size; j++)
            {
                newSol[i][j] = sol[i][j];
            }
        }

        return true;
    }

    //the permutation/backtracking function
    if (num != size * size) 
    {
        for (i = 0; i < 8; i++)
        {
            xPos = x + knight[i][0]; //moving the knight to a spot
            yPos = y + knight[i][1];

            if (pos[xPos + 2][yPos + 2] == 0 && sol[xPos][yPos] == 0) //checking if the spot is empty
            {
                //backtracking step but increments the num to continue adding to the board
                if (knightsTour(pos, sol, size, num + 1, xPos, yPos, newSol)) 
                {
                    return true;
                }
                // complete if true
            }
        }
        pos[x + 2][y + 2] = 0; //if the board can't complete backtracks till it can
        sol[x][y] = 0;
    }
    //if the board cannot permute any more

    return false;//for backtracking
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function will output our solution.
 *
 * @param[in]          sol - this is our solution array
 * @param[in]          size - this is the size of our board
 * @param[in]          loc - these are the coordinates that we started at
 * @param[in]          tourNum - this is what tour the output outputs.
 * @param[in, out]     fout - this is our output file
 *
 * @returns none
 *
 *****************************************************************************/
void printTour(int** sol, int size, int* loc, int tourNum, ostream& fout)
{
    int i = 0;
    int j = 0;

    //for printing a certain tour 
    fout << "Tour # " << tourNum << endl;
    fout << setw(9) << size << "x" << size  
        << " starting at (" << loc[0] << " , " << loc[1] << ")" << endl;

    if (isSafe(sol, size)) //checking if that tour is filled
    {
        for (i = 0; i < size; i++)
        {
            fout << endl << "      ";

            for (j = 0; j < size; j++)
            {
                fout << setw(4) << sol[i][j]; //print the tour
            }
            fout << endl;
        }
    }

    // output if the solution was not found
    else if (!isSafe(sol, size))
    {
        fout << endl << "      ";
        fout << "  No solutions for this case" << endl;
    }
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function will output our solution in the correct formatting.
 * the output can be desided on call.
 *
 * @param[in, out]          sol - this is our solution array
 * @param[in, out]          size - this is the size of our board
 *
 * @returns true - if the solution is done
 * @returns false - if the solution still has a 0 inside.
 *
 *****************************************************************************/
bool isSafe(int** sol, int size)
{
    int i;
    int j;

    //iterating through the board
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (sol[i][j] == 0) //checking if the board has any holes
            {
                return false;
            }
        }
    }
    return true;
}

/** **********************************************************************
 *  @author Yasas Wijesekara
 *
 *  @par Description
 *  closes all the files
 *
 *  @param[in] fin the file to be closed
 *  @param[in] fout the file to be openend
 *
 *  @returns none
 *
 *  @par Example
 *  @verbatim
    ifstream fin;
    ofstream fout;

    cleanUp(fin, fout);//the files are closed

    @endverbatim
 ************************************************************************/
void cleanUp(ifstream& fin, ofstream& fout)
{
    if (fout.is_open() == true)
    {
        fout.close();
    }
    if (fin.is_open() == true)
    {
        fin.close();
    }
    exit(0);
}
