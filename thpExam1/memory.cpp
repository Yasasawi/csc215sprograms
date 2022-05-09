/** *********************************************************************
 * @file
 *
 * @brief demonstrates the bubble sort, insertion sort,
 *        and selection sort.
 ***********************************************************************/
#include "netPBM.h"

 /** *********************************************************************
  * @author Yasas Wijesekara
  *
  * @par Description:
  * This function allocates a dynamic 2d array by first making a 1d array 
  * and then making 1d arrays at every index in the first 1d array
  *
  * @param[in] ptr - the name of the array
  * @param[in] row - the number of rows in the array
  * @param[in] cols - the number of cols in the array
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    pixel** ptr = nullptr; 
    int rows = 2; 
    int cols = 3;

    alloc2d(ptr, rows, cols); //makes a 2d array of size 2x3

    @endverbatim

  ***********************************************************************/
//function to create the 2d dynamic array
void alloc2d(pixel** &ptr, int row, int cols)
{
    int i;
    ptr = new (nothrow) pixel * [row];
    if (ptr == nullptr)
    {
        return;
    }
    for (i = 0; i < row; i++)
    {
        ptr[i] = new (nothrow) pixel[cols];
        if (ptr[i] == nullptr)
        {
            free2d(ptr, i);
            return;
        }
    }
    return;
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function frees up the dynamic 2d array; 
 *
 * @param[in] ptr - the array to be processed.
 * @param[in] rows - the number of rows in the array
 *
 * @returns none
 *
 * @par Example:
   @verbatim
    pixel** ptr = nullptr; 
    int rows = 2; 
    int cols = 3;

    alloc2d(ptr, rows, cols); //makes a 2d array of size 2x3
    free2d(ptr, rows); //frees up the array
   @endverbatim

 ***********************************************************************/
//freeing up the 2d arrays, essentially is the cleanup for the 2d arrays 
void free2d(pixel** &ptr, int rows)
{
    int i;
    if (ptr == nullptr)
    {
        return;
    }
    for (i = 0; i < rows; i++)
    {
        delete[] ptr[i];
    }
    delete[] ptr;
}
