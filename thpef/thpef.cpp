/** **************************************************************************
 * @file
 *
 *  @brief contains the main function snd testcases
 *
 *  Author: Yasas Wijesekara
 ****************************************************************************/
 /** **************************************************************************
  * @mainpage Program 3 - War
  *
  * @section course_section Course Information
  *
  * @author Yasas Wijesekara
  *
  * @par Professor:
  *         Dr. Roger L Schrader
  *
  * @par Course:
  *         CSC215 - M01 - Programming Techniques
  *
  * @par Location:
  *         McLaury - 330
  *
  * @date Due April 25, 2022
  *
  * @section program_section Program Information
  *
  * @details
  * This program utilizes the STL queue and a stack that I implemented myself
  * to then play the card game of war.
  * 
  *
  *
  * @section compile_section Compiling and Usage
  *
  * @par Compiling Instructions:
  *      put in either two files with card data in 
  *      or provide two numbers for the seed to play the game
  *
  * @par Usage:
    @verbatim
        thpef.exe -f file1.txt file2.txt
        Usage: thpef.exe -s seed1 seed2

    @endverbatim
  *
  *
  * @par Modifications and Development Timeline:
  * This is a link to gitlab's commit as an example. To view <a target="_blank"
  * href="https://gitlab.cse.sdsmt.edu/101083339/csc215s22programs">click here.</a>
  *
  *****************************************************************************/
#include "thpef.h"
#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"

const bool RUNCATCH = true;
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
    Catch::Session session;
    int result;
    queue<card> handOne;
    queue<card> handTwo;
    int seed1, seed2;
    int round = 0;
    int win;
    string p1File, p2File;
    ifstream p1Fin, p2Fin;
    bool tie = false;
    //for catch
    if (RUNCATCH)
    {
        result = session.run();
        if (result != 0)
        {
            cout << "Test cases didn't pass" << endl;
        }
    }
    if (argc != 4) //error checking for commandline args
    {
        cout << "Usage: thpef.exe -s 39483 9848" << endl;
        cout << "Usage: thpef.exe -f file1.txt file2.txt" << endl;
        exit(0);
    }
    //error checking to make sure the first option is valid
    if ((strcmp(argv[1], "-f") != 0) && (strcmp(argv[1], "-s") != 0))
    {
        cout << "Invalid Option: " << endl;
        cout << "thpef [option] ----- -----" << endl;
        cout << "option must be an -s or a -f" << endl;
        exit(0);
    }
    //code for getting the cards based off its an -f or -s
    if (strcmp(argv[1], "-f") == 0)
    {
        p1File = argv[2];
        p2File = argv[3];
        p1Fin.open(p1File);
        if (p1Fin.is_open() != true)
        {
            cleanUp(p1Fin, p2Fin);
        }
        p2Fin.open(p2File);
        if (p2Fin.is_open() != true)
        {
            cleanUp(p1Fin, p2Fin);
        }
        //reading and converting the file ints to card data
        fileHand(handOne, p1Fin);
        fileHand(handTwo, p2Fin);
    }
    if (strcmp(argv[1], "-s") == 0)
    {
        //convert the seeds to ints
        seed1 = stoi(argv[2]);
        seed2 = stoi(argv[3]);
        //make the hands from the seeds
        seedHand(handOne, seed1);
        seedHand(handTwo, seed2);
    }
    //code for playing the game
    while (handOne.size() != 0 && handTwo.size() != 0)
    {
        round++;
        playRound(handOne, handTwo);
    }
    if (handOne.size() == 0)
    {
        win = 2;
    }
    else
    {
        win = 1;
    }
    cout << "Player" << win << " wins after " << round << " rounds " << endl;
    cout << "Player 1 hand:" << handOne << endl;
    cout << "Player 2 hand:" << handTwo << endl;
    return 0;

}

//war game test cases
TEST_CASE("playRound - single card wins")
{
    card aCard;
    int i;
    ostringstream sout1, sout2;
    queue<card> p1, p2;
    int p1Cards[2] = { 4, 8 };
    int p2Cards[2] = { 2, 7 };
    for (i = 0; i < 2; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p1.push(aCard);
    }
    for (i = 0; i < 2; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p2.push(aCard);
    }
    SECTION("Single Card win")
    {
        playRound(p1, p2);
        sout1 << p1; // I overloaded the << operator to make this work
        sout2 << p2;
        REQUIRE(sout1.str() == " 8H 2H 4H");
        REQUIRE(sout2.str() == " 7H");
    }
    SECTION("Second round")
    {
        playRound(p1, p2);
        playRound(p1, p2);
        sout1 << p1; // I overloaded the << operator to make this work
        sout2 << p2;
        REQUIRE(sout1.str() == " 2H 4H 7H 8H");
        REQUIRE(sout2.str() == "");
    }
}

TEST_CASE("playRound - tie")
{
    card aCard;
    int i;
    ostringstream sout1, sout2;
    queue<card> p1, p2;
    int p1Cards[5] = { 5, 9, 4, 8, 3 };
    int p2Cards[5] = { 5, 8, 7, 6, 2 };
    for (i = 0; i < 5; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 3; // gave it a suit of hearts
        p1.push(aCard);
    }
    for (i = 0; i < 5; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p2.push(aCard);
    }
    playRound(p1, p2);
    sout1 << p1; // I overloaded the << operator to make this work
    sout2 << p2;
    REQUIRE(sout1.str() == " 3S 6H 7H 8H 5H 8S 4S 9S 5S");
    REQUIRE(sout2.str() == " 2H");

}

TEST_CASE("playRound - double tie")
{
    card aCard;
    int i;
    ostringstream sout1, sout2;
    queue<card> p1, p2;
    int p1Cards[7] = { 5, 9, 4, 8, 3, 2, 7 };
    int p2Cards[7] = { 5, 9, 4, 8, 3, 2, 1 };
    for (i = 0; i < 7; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 3; // gave it a suit of hearts
        p1.push(aCard);
    }
    for (i = 0; i < 7; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0; // gave it a suit of hearts
        p2.push(aCard);
    }
    playRound(p1, p2);
    sout1 << p1; // I overloaded the << operator to make this work
    sout2 << p2;
    REQUIRE(sout1.str() == " 1H 2H 3H 8H 4H 9H 5H 7S 2S 3S 8S 4S 9S 5S");
    REQUIRE(sout2.str() == "");

}

//stack test cases
TEST_CASE("pop")
{

    myStack<int> stack;
    int item;

    REQUIRE(stack.push(30) == true);
    REQUIRE(stack.push(40) == true);
    REQUIRE(stack.push(50) == true);
    REQUIRE(stack.push(60) == true);
    REQUIRE(stack.push(70) == true);
    REQUIRE(stack.push(20) == true);
    stack.print(cout, " ");
    cout << endl;
    REQUIRE(stack.pop(item) == true);
    stack.print(cout, " ");
    cout << endl;
    cout << item << endl;
}

TEST_CASE("top")
{

    myStack<int> stack;
    int item;

    REQUIRE(stack.push(30) == true);
    REQUIRE(stack.push(40) == true);
    REQUIRE(stack.push(50) == true);
    REQUIRE(stack.push(60) == true);
    REQUIRE(stack.push(70) == true);
    REQUIRE(stack.push(100) == true);

    REQUIRE(stack.top(item) == true);

    cout << item << endl;
}

TEST_CASE("push")
{
    myStack<int> stack;

    REQUIRE(stack.push(1) == true);
    REQUIRE(stack.push(2) == true);
    REQUIRE(stack.push(3) == true);
    REQUIRE(stack.push(4) == true);
    REQUIRE(stack.push(5) == true);
    REQUIRE(stack.push(6) == true);

    REQUIRE(stack.size() == 6);
    stack.print(cout, " ");
    cout << endl;
}

TEST_CASE("size")
{
    myStack<int> stack;

    REQUIRE(stack.push(1932) == true);
    REQUIRE(stack.push(2) == true);
    REQUIRE(stack.push(32) == true);
    REQUIRE(stack.push(70374) == true);
    REQUIRE(stack.push(5123) == true);
    REQUIRE(stack.push(412) == true);

    REQUIRE(stack.size() == 6);
}
