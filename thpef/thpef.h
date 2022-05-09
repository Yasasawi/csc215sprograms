/** **************************************************************************
 * @file
 *
 *  @brief contains the function definitions and prototypes 
 *
 *  Author: Yasas Wijesekara
 ****************************************************************************/
#pragma once
#include <random>
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

//card structure
/**
* @brief  the storage container representing a card
*/
struct card
{
    int faceValue; /*!< the cards face value*/
    int suit; /*!< the cards suit */
};

//stack class prototype
/** **************************************************************************
 * @class   myStack
 *
 * @brief   A linked list based stack
 ****************************************************************************/
template <typename TY> 
class myStack
{
public:
    myStack();
    ~myStack();

    bool pop(TY& item);
    bool push(TY item);
    bool top(TY& item);
    bool isEmpty();
    int size();
    void print(ostream& out, string seperator = ", "); //for debugging

private:
    /**
 * @brief  the storage container for each item in the stack
 */
    struct node
    {
        TY data;    /*!< the item */
        node* next;     /*!< pointer to the remaining nodes in stack */
    };
    node* headptr;      /*!< The location of the first node in the stack */
};

/** ***************************************************************************
 *                         Function Prototypes
******************************************************************************/
bool seedHand(queue<card>& hand, int seed);
void playRound(queue<card>& player1, queue<card>& player2);
void printHand(queue<card>& hand, ostream& out);
bool dupeCard(queue<card>& hand, card checkCard);
bool fileHand(queue<card>& hand, ifstream& fin);
void deal(myStack<card>& d1, myStack<card>& d2, queue<card>& handOne, queue<card>& handTwo);
void cleanUp(ifstream& fin, ifstream& fin2);
ostream& operator<<(ostream& out, queue<card>& queue);
void getDiscard(myStack<card>& discard, queue<card>& hand);



//card functions
/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function plays a game of war, given two players, which are represented 
 * by queues.
 *
 * @param[in]     player1 - a queue to represent player ones hand of cards
 * @param[in]     player2 - a queue to represent player twos hand of cards
 *
 * @returns nothing
 *
 *****************************************************************************/
void playRound(queue<card>& player1, queue<card>& player2)
{
    myStack<card> discardOne;
    myStack<card> discardTwo;
    int i = 0;
    bool tie = false;
    card p2Card, p1Card;
    deal(discardOne, discardTwo, player1, player2);
    discardOne.top(p1Card); //get the card
    discardTwo.top(p2Card);
    //deal a card
    if (p1Card.faceValue > p2Card.faceValue)//playerone has high card
    {
        getDiscard(discardTwo, player1); //take your opponenents discard
        getDiscard(discardOne, player1); //take your discard
    }
    if (p1Card.faceValue < p2Card.faceValue)//playertwo has high card
    {
        getDiscard(discardOne, player2); //take opponents discard
        getDiscard(discardTwo, player2); //take your discard
    }
    else if (p1Card.faceValue == p2Card.faceValue)//for the tie case
    {
        tie = true;
        while (tie)//go until no tie
        {
            for (i = 0; i < 3; i++)
            {
                deal(discardOne, discardTwo, player1, player2);
            }
            discardOne.top(p1Card); //get the first card
            discardTwo.top(p2Card);
            if (p1Card.faceValue != p2Card.faceValue)
            {
                tie = false;
            }
        }
        if (p1Card.faceValue > p2Card.faceValue)//playerone has high card
        {
            getDiscard(discardTwo, player1); //take your opponenents discard
            getDiscard(discardOne, player1); //take your discard
        }
        if (p1Card.faceValue < p2Card.faceValue)//playertwo has high card
        {
            getDiscard(discardOne, player2); //take opponents discard
            getDiscard(discardTwo, player2); //take your discard
        }
    }
}


/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function simulates dealing a card in war.
 *
 * @param[in]     d1 - a stack to represent player ones discard pile
 * @param[in]     d2 - a stack to represent player twos discard pile
 * @param[in]     handOne - a queue to represent player ones hand of cards
 * @param[in]     handTwo - a queue to represent player twos hand of cards
 *
 * @returns nothing
 *
 *****************************************************************************/
void deal(myStack<card>& d1, myStack<card>& d2, queue<card>& handOne, queue<card>& handTwo)
{
    card p1, p2;
    //function to simulate dealing a card
    p1 = handOne.front();
    p2 = handTwo.front();

    //taking the card out of the original queue of cards
    handOne.pop();
    handTwo.pop();

    //placing the card into the discard
    d1.push(p1);
    d2.push(p2);
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function gets the discard pile and puts it in the hand of the player
 *
 * @param[in]     discard - a stack to represent a discard pile
 * @param[in]     hand - a queue to represent a players hand of cards
 *
 * @returns nothing
 *
 *****************************************************************************/
void getDiscard(myStack<card>& discard, queue<card>& hand)
{
    int size;
    int i;
    card theCard;
    size = discard.size();
    for (i = 0; i < size; i++)
    {
        //take the card out of the discard
        discard.pop(theCard);
        //put the card into the hand
        hand.push(theCard);
    }
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function fills a hand with cards from a file
 *
 * @param[in]     hand - a queue to represent a players hand of cards
 * @param[in]     fin - the file stream
 *
 * @returns true if done successfully
 *
 *****************************************************************************/
bool fileHand(queue<card>& hand, ifstream& fin)
{
    card aCard;
    int cardValue;
    while(fin >> cardValue)
    {
        aCard.faceValue = cardValue % 13; // 0=ace, 1=deuce, ... 9=ten, 10=jack, 11=queen, 12=king
        aCard.suit = cardValue / 13; // 0=hearts, 1=diamonds, 2=clubs, 3=spades
        hand.push(aCard);
    }
    return true; 
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The function is for the seed, it just makes sure we do not have 
 * duplicate cards when reading in.
 *
 * @param[in]     hand - a queue to represent a players hand of cards
 * @param[in]     checkCard - the card its checking
 *
 * @returns true if done successfully
 *
 *****************************************************************************/
bool dupeCard(queue<card>& hand, card checkCard)
{
    int i;
    size_t size; 
    card theCard;
    bool isDupe = false;
    size = hand.size();
    for (i = 0; i < size; i++)
    {
        theCard = hand.front(); //get the card
        hand.pop();
        //checks for duplicates
        if (theCard.faceValue == checkCard.faceValue && theCard.suit == checkCard.suit)
        {
            isDupe = true;
        }
        hand.push(theCard); //put the card back in to cycle through
    }
    return isDupe;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function prints out a hand
 *
 * @param[in]     hand - a queue to represent a players hand of cards
 * @param[in]     out - the output stream
 *
 * @returns nothing
 *
 *****************************************************************************/
void printHand(queue<card>& hand, ostream& out)
{
    int i;
    size_t size;
    char suits;
    card theCard;
    size = hand.size();
    for (i = 0; i < size; i++)
    {
        //set the card to the first one
        theCard = hand.front();
        hand.pop();
        //assign the suit character based off of the suit value
        if (theCard.suit == 0)
        {
            suits = 'H';
        }
        if (theCard.suit == 1)
        {
            suits = 'D';
        }
        if (theCard.suit == 2)
        {
            suits = 'C';
        }
        if (theCard.suit == 3)
        {
            suits = 'S';
        }
        // put the card at the back to cycle through the queue
        out << " " << theCard.faceValue << suits;
        hand.push(theCard);
    }
}


/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function fills a hand with cards from a random seed
 *
 * @param[in]     hand - a queue to represent a players hand of cards
 * @param[in]     seed - the random seed
 *
 * @returns true if done successfully
 *
 *****************************************************************************/
bool seedHand(queue<card>& hand, int seed)
{
    default_random_engine generator(seed); // use a different seed for each player.
    uniform_int_distribution<int> distribution(0, 51);

    card theCard;
    int cardValue;

    while (hand.size() != 52)
    {
        cardValue = distribution(generator); // will give a number between 0 and 51 inclusive.
        theCard.faceValue = cardValue % 13; // 0=ace, 1=deuce, ... 9=ten, 10=jack, 11=queen, 12=king
        theCard.suit = cardValue / 13;
        if (!dupeCard(hand, theCard))
        {
            hand.push(theCard);
        }
    }
    return true; 
}

//stack functions
/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The constructor for the stack class
 *
 * @returns nothing
 *
 *****************************************************************************/
template <typename TY>
myStack<TY>::myStack()
{
    headptr = nullptr;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The destructor for the stack class
 *
 * @returns nothing
 *
 *****************************************************************************/
template <typename TY>
myStack<TY>::~myStack()
{
    node* temp;
    node* next;
    next = nullptr;
    temp = headptr;

    if (headptr == nullptr)
    {
        return;
    }
    while (temp != nullptr)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
    headptr = nullptr;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The pop function for the stack class, takes an item off the stack
 * and returns it
 * 
 * param[in] item - the item that is popped out
 *
 * @returns true if done successfully
 *
 *****************************************************************************/
template <typename TY>
bool myStack<TY>::pop(TY& item)
{
    node* temp;

    //check for empty stack
    if (headptr == nullptr)
    {
        return false;
    }
    else
    {
        // Assign headptr to temp
        temp = headptr;
        item = temp->data;
        // Assign second node to headptr
        headptr = headptr->next;
        //delete the node
        delete temp;
        return true;
    }
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The push function for the stack class, puts an item on top of the stack
 *
 * param[in] item - the item that is popped out
 *
 * @returns true if done successfully
 *
 *****************************************************************************/
template <typename TY>
bool myStack<TY>::push(TY item)
{

    // Create new node temp 
    node* temp = new (nothrow) node;
    if (!temp)
    {
        return false;
    }

    // Initialize data into temp data field
    temp->data = item;

    // Put top pointer reference into temp link
    temp->next = headptr;

    // Make temp as top of Stack
    headptr = temp;
    return true;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The isEmpty function checks if the stack is empty
 *
 *
 * @returns true if the stack is empty
 *
 *****************************************************************************/
template <typename TY>
bool myStack<TY>::isEmpty()
{
    //checking headptr to see if it is equal to nullptr
    if (headptr == nullptr)
    {
        return true;
    }
    return false;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The top function for the stack class gets the first value of the stack
 *
 * param[in] item - the item that is first in the stack
 *
 * @returns true if there is something there on top of the stack
 *
 *****************************************************************************/
template <typename TY>
bool myStack<TY>::top(TY& item)
{
    if (headptr == nullptr) //making sure the stack isnt empty
    {
        return false;
    }
    
    item = headptr->data; //copying the first item into the variable
    return true;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The size function for the stack class
 *
 * @returns an integer size of the stack
 *
 *****************************************************************************/
template <typename TY>
int myStack<TY>::size()
{
    node* temp = headptr;
    int size = 0;
    while (temp != nullptr)
    {
        size++;
        temp = temp->next;
    }
    return size;
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * The print function for the stack class for debugging
 *
 * param[in] out - the the output stream
 * param[in] separator - the seperator between the values of the stack
 *
 * @returns nothing
 *
 *****************************************************************************/
template <class TY> 
void myStack<TY>::print(ostream& out, string seperator)
{
    node* temp;
    temp = headptr;
    while (temp != nullptr)
    {
        if (temp->next == nullptr)
        {
            out << temp->data;
        }
        else
        {
            out << temp->data << seperator;
        }
        temp = temp->next;
    }
}

//helper functions
/** **********************************************************************
 *  @author Yasas Wijesekara
 *
 *  @par Description
 *  closes all the files
 *
 *  @param[in] fin the file to be closed
 *  @param[in] fin2 the file to be closed
 *
 *  @returns none
 *
 *  @par Example
 *  @verbatim
    ifstream fin;
    ifstream fin2;

    cleanUp(fin, fin2);//the files are closed

    @endverbatim
 ************************************************************************/
void cleanUp(ifstream& fin, ifstream& fin2)
{
    fin2.close();
    fin.close();
    exit(0);
}

/** ***************************************************************************
 * @author Yasas Wijesekara
 *
 * @par Description:
 * This function is the overloaded operator << for queues 
 *
 * @param[in]     out - the output stream
 * @param[in]     queue - the queue being outputted
 *
 * @returns the output stream
 *
 *****************************************************************************/
ostream& operator<<(ostream& out, queue<card>& queue)
{
    printHand(queue, out);
    cout << endl;
    return out;
}
