/** *********************************************************************
 * @file
 *
 * @brief  Prototypes
 ***********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;
/************************************************************************
 *             Constant Variables, defines and Enums
 ***********************************************************************/
#ifndef __NETPBM__H__
#define __NETPBM__H__

 /** typedef for the pixel to be used to represent the image pixels */
typedef unsigned char pixel; 

/**a structure to represent the image file and arrays for the image rgb pixels*/
struct image
{
    /*@{*/
    string magicNumber; /**< the magic number of the image*/
    string comment; /**< the comment in the header to be formatted*/
    int rows; /**< the number of rows in the arrays, or the y axis of the image */
    int cols; /**< the number of colomns in the arrays, or the x axis of the image */
    pixel** redGray; /**< the red and gray color array */
    pixel** green; /**< the green color array*/
    pixel** blue; /**< the blue color array */
    /*@}*/
};


//print functions
void printArrays(image& img, ofstream& fout);
void printArraysBin(image& img, ofstream& fout);
void printGrayscaleAscii(image& img, ofstream& fout);
void printGrayscalesBin(image& img, ofstream& fout);
void headerPrint(image& img, ofstream& fout);

void cleanUp(ifstream& input, ofstream& output);

//memory functions
void free2d(pixel**& ptr, int rows);
void alloc2d(pixel**& ptr, int row, int cols);

//fill functions
void asciiArrayFill(image& img, ifstream& fin);
void binaryFill(image& img, ifstream& fin);
void getHeader(image& img, ifstream& fin);

//image operations
void sepia(image& img);
void grayscale(image& img);
void flipX(image& img);
void flipY(image& img);
void rotateCW(image& img); 
void rotateCCW(image& img);
#endif