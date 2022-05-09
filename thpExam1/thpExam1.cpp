/** *********************************************************************
 * @file
 *
 * @brief demonstrates image editing functions as well as binary and ascii file handling
 ***********************************************************************/

 /** ********************************************************************
 *
 * @mainpage thpExam1 - Image Manipulation
 *
 * @section M01 Programming Techniques
 *
 * @authors Yasas Wijesekara
 *
 * @date March 8, 2022
 *
 * @par Instructor:
 *         Professor Schrader
 *
 * @par Course:
 *         CSC 215 - Section 1 - 9:00 am
 *
 * @par Location:
 *         Classroom Building - CB329
 *
 * @section program_section Program Information
 *
 * @details This program will take in either a binary or an ascii pgm file and be able to perform different operations on 
 * file to make a different image with different filters or rotate or flip the image, this will be done through the 
 * inputting of the data into 2d arrays in a structure of type pixel, and utilizing ptrs to handle the values 
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\>thpExam1.exe --option --outputtype basename image.ppm

        --option - the name of the transformation being done
        --outputtype - the type of data that the file is outputting 
        basename - name of the file to output contents of transformed image
        image.ppm - the name of the original input image
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  no known bugs
 *
 * @todo error messages for allocating memory and getting incorrect magic numbers 
 *
 * @par Modifications and Development Timeline:

   Gitlab commit log, <a href = "https://gitlab.cse.sdsmt.edu/101083339/csc215s22programs"
   target="_blank">
   Click Here.</a>
 *
 ***********************************************************************/
#include "netPBM.h"
/** *********************************************************************
 * @author Yasas
 *
 * @par Description:
 * This is the starting point to the program.  It will get the input file, the output file
 * and the transformation and the output file type from the commandline arguments
 * if not supplied at least the minimum output file arguements it will display an
 * error message
 *
 *
 * @param[in] argc - the number of arguments from the command prompt.
 * @param[in] argv - a 2d array of characters containing the arguments.
 *
 * @returns 0 to end the program
 *
 * @verbatim
   see usage statement above.
   @endverbatim
 *
 ***********************************************************************/
int main(int argc, char** argv)
{
    image img;
    string extension;
    string inputFile, outputFile, fileType, editType;
    ifstream fin;
    ofstream fout;
    int maxVal = 255;
    //checking for arguements
    if (argc < 4)
    {
        cout << "Usage: thpExam.exe --outputtype basename image.ppm" << endl;
        cleanUp(fin, fout);
    }

    //accessing the files and checking if they opened/exist
    if (argc == 5)
    {
        inputFile = argv[4];
        editType = argv[1];
        fileType = argv[2];
        outputFile = argv[3];
    }
    else
    {
        inputFile = argv[3];
        outputFile = argv[2];
        fileType = argv[1];
    }

    //changing the file extension if grayscale is called
    if (editType == "--grayscale")
    {
        extension = ".pgm";
        outputFile = outputFile + extension;
    }
    else
    {
        //putting the ppm extension at the end of the output file
        extension = ".ppm";
        outputFile = outputFile + extension;
    }

    //error checking
    fin.open(inputFile, ios::in | ios::binary);
    if (fin.is_open() != true)
    {
        cout << "Unable to open input file: " << inputFile << endl;
        cleanUp(fin, fout);
    }
    fout.open(outputFile, ios::out | ios::trunc | ios::binary);
    if (fin.is_open() != true)
    {
        cout << "Unable to open output file: " << outputFile << endl;
        cleanUp(fin, fout);
    }

    //getting the header
    getHeader(img, fin);

    //allocating the 2d arrays for each color band (redGray, blue, green) and error checking for if they cannot allocate
    alloc2d(img.redGray, img.rows, img.cols);
    alloc2d(img.green, img.rows, img.cols);
    alloc2d(img.blue, img.rows, img.cols);

    //getting an ascii file and reading it 
    if (img.magicNumber == "P3")
    {
        //getting the data and putting it into the 2d arrays
        asciiArrayFill(img, fin);
    }
    if (img.magicNumber == "P6")
    {
        binaryFill(img, fin);
    }

    //if statements to read image operations
    if (editType == "--sepia")
    {
        sepia(img);
    }
    else if (editType == "--flipX")
    {
        flipX(img);
    }
    else if (editType == "--flipY")
    {
        flipY(img);
    }
    else if (editType == "--rotateCW")
    {
        rotateCW(img);
    }
    else if (editType == "--rotateCCW")
    {
        rotateCCW(img);
    }

    //output for ascii grayscale file
    if (fileType == "--ascii" && editType == "--grayscale")
    {
        grayscale(img);
        img.magicNumber = "P2";
        headerPrint(img, fout);
        fout << maxVal << endl;
        printGrayscaleAscii(img, fout);
    }
    else if (fileType == "--binary" && editType == "--grayscale") //outputting a binary grayscale file
    {
        grayscale(img);
        img.magicNumber = "P5";
        headerPrint(img, fout);
        fout << maxVal << endl;
        printGrayscalesBin(img, fout);
    }
    else if (fileType == "--binary") //outputting a binary file 
    {
        img.magicNumber = "P6";
        headerPrint(img, fout);
        fout << maxVal << endl; 
        printArraysBin(img, fout);
    }
    else if (fileType == "--ascii") //outputting an ascii file
    {
        img.magicNumber = "P3";
        headerPrint(img, fout);
        fout << maxVal << endl;
        printArrays(img, fout);
    }

    //freeing arrays and closing files
    free2d(img.redGray, img.rows);
    free2d(img.green, img.rows);
    free2d(img.blue, img.rows);
    cleanUp(fin, fout);
    return 0;
}
