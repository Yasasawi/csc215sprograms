/** *********************************************************************
 * @file
 *
 * @brief demonstrates the bubble sort, insertion sort,
 *        and selection sort.
 ***********************************************************************/
#include "netPBM.h"

 /** **********************************************************************
  *  @author Yasas Wijesekara
  *
  *  @par Description
  *  closes all the files
  *
  *  @param[in] input the file to be closed
  *  @param[in] output the file to be closed
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
//cleanUp function to handle closing the files when done and exiting the program
void cleanUp(ifstream& input, ofstream& output)
{
    if (output.is_open() == true)
    {
        output.close();
    }
    if (input.is_open() == true)
    {
        input.close();
    }
    input.close();
    exit(0);
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function gets the header of the input file using get lines and ifstream's to get the values and comments
 *
 * @param[in] img - the image structure to put the values into
 * @param[in] fin - the input file to look into 
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ifstream fin; 

   getHeader(img, fin); //gets the relavent header lines and puts them into the relavent spots in the structures

   @endverbatim

 ***********************************************************************/
//getting the header of the file 
void getHeader(image& img, ifstream& fin)
{
    int maxVal;
    getline(fin, img.magicNumber, '\n');
    getline(fin, img.comment, '\n');
    fin >> img.cols;
    fin >> img.rows;
    fin >> maxVal;
    fin.ignore();
}
/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This is just a function for printing out a grayscale array in the ascii format
 *
 * @param[in] img - the image data
 * @param[in] fout - the output file to put the values
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ofstream fout;

   grayscale(img);
   printGrayscaleAscii(img, fout);

   @endverbatim

 ***********************************************************************/
void printGrayscaleAscii(image& img, ofstream& fout)
{
    int i, j;
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fout << (int)img.redGray[i][j] << endl;
        }
    }
}
/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This is just a function for printing out a grayscale array in the binary format
 *
 * @param[in] img - the image data
 * @param[in] fout - the output file to put the values
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ofstream fout;

   grayscale(img);
   printGrayscalesBin(img, fout); //prints out the arrays to the output file

   @endverbatim

 ***********************************************************************/
void printGrayscalesBin(image& img, ofstream& fout)
{
    int i, j;
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fout.write((char*)&img.redGray[i][j], sizeof(pixel));
        }
    }
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This is just a function for printing out the color 2d arrays in the ascii format
 *
 * @param[in] img - the image data
 * @param[in] fout - the output file to put the values
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ofstream fout;

   printArrays(img, fout); //prints out the arrays to the output file

   @endverbatim

 ***********************************************************************/
//for printing an ascii array
void printArrays(image& img, ofstream& fout)
{
    int i, j;
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fout << (int)img.redGray[i][j] << endl;
            fout << (int)img.green[i][j] << endl;
            fout << (int)img.blue[i][j] << endl;
        }
    }
}
/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This is just a function for printing out the color 2d arrays in the binary format
 *
 * @param[in] img - the image data
 * @param[in] fout - the output file to put the values
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ofstream fout;

   printArraysBin(img, fout); //prints out the arrays to the output file

   @endverbatim

 ***********************************************************************/
//for printing a binary array 
void printArraysBin(image& img, ofstream& fout)
{
    int i, j;
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fout.write((char*)&img.redGray[i][j], sizeof(pixel));
            fout.write((char*)&img.green[i][j], sizeof(pixel));
            fout.write((char*)&img.blue[i][j], sizeof(pixel));
        }
    }
}
/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * this is a function that takes the values from the p3 ascii array and puts them into the arrays
 *
 * @param[in] img - the image data
 * @param[in] fin - the input file to get the values from
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ifstream fin;
   ofstream fout;

   asciiArrayfill(img, fin); //gets the values from the input file
   printArrays(img, fout); // prints out the arrays

   @endverbatim

 ***********************************************************************/
void asciiArrayFill(image& img, ifstream& fin)
{
    int i;
    int j;
    int temp_value;


    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fin >> temp_value;
            img.redGray[i][j] = temp_value;
            fin >> temp_value;
            img.green[i][j] = temp_value;
            fin >> temp_value;
            img.blue[i][j] = temp_value;
        }
    }
}
/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * this is a function that takes the values from the p6 binary array and puts them into the arrays
 *
 * @param[in] img - the image data
 * @param[in] fin - the input file to get the values from
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ifstream fin;
   ofstream fout;

   binaryfill(img, fin); //gets the values from the input file
   printArraysBin(img, fout); // prints out the arrays

   @endverbatim

 ***********************************************************************/
void binaryFill(image& img, ifstream& fin)
{
    int i, j;
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            fin.read((char*)&img.redGray[i][j], sizeof(pixel));
            fin.read((char*)&img.green[i][j], sizeof(pixel));
            fin.read((char*)&img.blue[i][j], sizeof(pixel));
        }
    }
}
/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * this is a function that just prints out the header
 *
 * @param[in] img - the image data
 * @param[in] fout - the output file to print to
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;
   ifstream fin;
   ofstream fout;

   getHeader(img, fin); //gets the values from the input file
   headerPrint(img, fout); // prints out the header

   @endverbatim

 ***********************************************************************/
//prints the header
void headerPrint(image& img, ofstream& fout)
{
    fout << img.magicNumber << endl;
    fout << img.comment << endl;
    fout << img.cols << ' ' << img.rows << endl;
}