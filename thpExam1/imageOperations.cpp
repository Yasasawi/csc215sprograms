/** *********************************************************************
 * @file
 *
 * @brief image edit functions that augment the color and orientation of the image 
 ***********************************************************************/
#include "netPBM.h"
 /** *********************************************************************
  * @author Yasas Wijesekara
  *
  * @par Description:
  * This function flips the image on its x axis by reversing the row values
  * creating a mirror effect across the x - axis
  *
  * @param[in] img - the image to be processed
  *
  * @returns none
  *
  * @par Example:
    @verbatim
    image img;

    flipX(img); //changes the row and colomn values of the image to flip it 

    @endverbatim

  ***********************************************************************/
void flipX(image& img)
{
    int i, j, mid;
    //set mid to half the size of the rows
    mid = img.rows / 2; 
    for (i = 0; i < mid; i++)
    {
        for(j = 0; j != img.cols; j++)
        {
            //swap the current values with the ones towards the end of the rows
            swap(img.redGray[i][j], img.redGray[img.rows - 1 - i][j]);
            swap(img.green[i][j], img.green[img.rows - 1 - i][j]);
            swap(img.blue[i][j], img.blue[img.rows - 1 - i][j]);
        }
    }
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function flips the image on its y axis by reversing the colomn values
 * creating a mirror effect across the y - axis
 *
 * @param[in] img - the image to be processed
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;

   flipY(img); //changes the row and colomn values of the image to flip it

   @endverbatim

 ***********************************************************************/
void flipY(image& img)
{
    int i, j, mid;
    //mid to half the size of the colomns
    mid = img.cols / 2;
    //iterate through the 2d array
    for (i = 0; i != img.rows; i++)
    {
        for (j = 0; j < mid; j++)
        {
            //swap the current value with values torwards the end of the colomns
            swap(img.redGray[i][j], img.redGray[i][img.cols - 1 - j]);
            swap(img.green[i][j], img.green[i][img.cols - 1 - j]);
            swap(img.blue[i][j], img.blue[i][img.cols - 1 - j]);
        }
    }
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function turns the color of the image given to 
 * grayscale
 *
 * @param[in] img - the image to be processed
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;

   grayscale(img); //changes the color arrays to one array and uses an equation to make them grayscale
   @endverbatim

 ***********************************************************************/
void grayscale(image& img)
{
    int i, j;
    //iterate through the 2d array
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            //set the redGray array to the new grayscale values with this equation
            img.redGray[i][j] = .3 * img.redGray[i][j] + .6 * img.green[i][j] + .1 * img.blue[i][j];
        }
    }
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function turns the color of the image given to
 * sepia
 *
 * @param[in] img - the image to be processed
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;

   grayscale(img); //changes the color arrays with equations to make them match the sepia filter
   @endverbatim

 ***********************************************************************/
void sepia(image& img)
{
    //declare temp variables
    int tr, tg, tb, R, G, B;
    int i, j;
    //iterate through the 2d arrays 
    for (i = 0; i < img.rows; i++)
    {
        for (j = 0; j < img.cols; j++)
        {
            //set the temp values to the array value
            R = (int)img.redGray[i][j];
            G = (int)img.green[i][j];
            B = (int)img.blue[i][j];

            //calculate the new sepia values and put them into the other set of temp values
            tr = 0.393 * R + 0.769 * G + 0.189 * B;
            tg = 0.349 * R + 0.686 * G + 0.168 * B;
            tb = 0.272 * R + 0.534 * G + 0.131 * B;

            //if the value goes higher than 255 bring it back down to 255
            if (tr > 255)
            {
                tr = 255; 
            }
            if (tg > 255)
            {
                tg = 255;
            }
            if (tb > 255)
            {
                tb = 255;
            }

            //replace the current value with the new sepia one
            img.redGray[i][j] = tr;
            img.green[i][j] = tg;
            img.blue[i][j] = tb;
        }
    }
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function rotates the image clockwise by swapping the row and colomn values
 * and then reading in the data to the rows and colomns respectfully
 *
 * @param[in] img - the image to be processed
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;

   rotateCW(img); //rotates the image clockwise
   @endverbatim

 ***********************************************************************/
void rotateCW(image& img)
{
    //declare temp variables
    int i, j;
    pixel** oldRedGray = nullptr;
    pixel** oldGreen = nullptr;
    pixel** oldBlue = nullptr;
    pixel** redGrayNew = nullptr;
    pixel** greenNew = nullptr;
    pixel** blueNew = nullptr;

    //allocate 3 new 2d arrays but switch the colomns and rows 
    alloc2d(redGrayNew, img.cols, img.rows);
    alloc2d(greenNew, img.cols, img.rows);
    alloc2d(blueNew, img.cols, img.rows);

    //set the current color values to the old arrays 
    oldRedGray = img.redGray;
    oldGreen = img.green;
    oldBlue = img.blue;

    //read in the colomns and row values into the new array but flipped to fit the new image
    for (i = 0; i < img.cols; i++)
    {
        for (j = 0; j < img.rows; j++)
        {
            redGrayNew[i][j] = oldRedGray[img.rows - 1 - j][i];
            greenNew[i][j] = oldGreen[img.rows - 1 - j][i];
            blueNew[i][j] = oldBlue[img.rows - 1 - j][i];
        }
    }

    //set the current image values to the new ones
    img.redGray = redGrayNew;
    img.green = greenNew;
    img.blue = blueNew;
    //swap the rows and colomns for main 
    swap(img.rows, img.cols);
}

/** *********************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function rotates the image counter clockwise by swapping the row and colomn values
 * and then reading in the data to the rows and colomns respectfully but this time 
 * reading in the data backwards on the colomn side backwards to rotate it counter clockwise
 *
 * @param[in] img - the image to be processed
 *
 * @returns none
 *
 * @par Example:
   @verbatim
   image img;

   rotateCCW(img); //rotates the image counterclockwise clockwise
   @endverbatim

 ***********************************************************************/
void rotateCCW(image& img)
{
    //declare temp variables
    int i, j;
    pixel** oldRedGray = nullptr;
    pixel** oldGreen = nullptr;
    pixel** oldBlue = nullptr;
    pixel** redGrayNew = nullptr;
    pixel** greenNew = nullptr;
    pixel** blueNew = nullptr;

    //allocate 3 new 2d arrays but switch the colomns and rows 
    alloc2d(redGrayNew, img.cols, img.rows);
    alloc2d(greenNew, img.cols, img.rows);
    alloc2d(blueNew, img.cols, img.rows);

    //set the current color values to the old arrays 
    oldRedGray = img.redGray;
    oldGreen = img.green;
    oldBlue = img.blue;

    //read in the colomns and row values into the new array but flipped to fit the new image
    for (i = 0; i < img.cols; i++)
    {
        for (j = 0; j < img.rows; j++)
        {
            redGrayNew[i][j] = oldRedGray[j][img.cols - 1 - i];
            greenNew[i][j] = oldGreen[j][img.cols - 1 - i];
            blueNew[i][j] = oldBlue[j][img.cols - 1 - i];
        }
    }

    //set the current image values to the new ones
    img.redGray = redGrayNew;
    img.green = greenNew;
    img.blue = blueNew;
    //swap the rows and colomns for main 
    swap(img.rows, img.cols);
}
