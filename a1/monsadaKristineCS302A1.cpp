/** Name: Kristine Monsada, 2001381858, Assignment 1*
Description: a type of solitare game called "accordions"
    cards will be pushed on to stacks based on matching
    ranks or suits until no more moves can be made or 1 stack left
Input: A1input.txt, a file that contains data of 2 sets of 52 cards
    program will finish reading until "#" sign/eof*
Output: the number of piles of stacks with the top of the stack revealed
    as well as how many cards are in each stack */

// code for mem leaks
/*
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#define ___FLAG
#define _TEST_ _CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_DEBUG ); _CrtDumpMemoryLeaks(); _ASSERT( _CrtCheckMemory( ) );
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif
*/

#include <iostream>
#include <fstream>
#include <string>
#include "myStack.h"

using namespace std;

/** function_identifier: function that iterates though the whole stackArray 
       to determine anymore possible moves
* parameters: main stack counter and the actual stackObject
* return value: false, if found a match & true if no more matches found */

// function declaration to determine if there is no more possibile moves left
bool noMoreMoves(int stackSize, myStack<string>* stackArray);

int main() {

    // area for all declared variables
    ifstream inFile;
    string fileName;

    // this initializes the 52 myStack objects
    myStack <string> cardStack[52];
    string holder = "";
    bool doneReading = false;

    // user entered file for data stuffs
    cout << "File name: ";
    // read in file name
    cin >> fileName;
    // opens the file
    inFile.open(fileName.c_str());

    // if wrong file was read in, this will keep reprompting until opened
    // else, if opened correctly, will skip this block
    while (inFile.fail()) {
        // clears failbit
        inFile.clear();
        // user entered file for data stuffs
        cout << "File name: ";
        cin >> fileName;
        // opens the file
        inFile.open(fileName.c_str());

        // proceeed to rest of program when opened properly
        if (inFile.is_open())
            break;
    }

    // read the first element first to determine if we continue reading or not
    inFile >> holder;

    while (!doneReading) {
    // read all the elements inside the file
    // this will already read in both stacks and store them into a string array
    // then each element will be pushed into one myStack object
    // string array that contains all data read

        // if its not a #, we can assume 51 other cards will be following 
        if (holder != "#") {

            // push the read data into the cardStack object
            for (int i = 0; i < 52; i++) {
                cardStack[i].push(holder);
                // keep on reading until all 52 cards have been made
                inFile >> holder;
            }

        }
        // signifies no more data to be read
        else if(holder == "#") {
            doneReading = true;
            break;
        }

        // main counter
        int stackLength = 52;
        // for debugging purposes - pls ignore!
        bool done = false;

        while (stackLength > 1 && !noMoreMoves(stackLength, cardStack)) {

            // moveArray() - this will move ONLY one stack at a time starting from end, start right going left
            for (int i = 1; i < stackLength; i++) {
                /*/
                 temp = current cardStack index
                 first = immediate left card
                 third = third card to the left,
                 we save these cards in a string array to compare their 0th 
                 and 1st element bc that holds rank/suit
                */
                string tempCardCheck = cardStack[i].peek();
                string firstCard = cardStack[i - 1].peek();
                string thirdCard;

                // check so third card doesnt get out of bounds
                if (i >= 3) {
                    thirdCard = cardStack[i - 3].peek();
                }
                // used for popping bc returns the top
                string newTop = "";

                // have a check if i = 3
                // when index i, last time for a left check
                /*
                    the following if statements will proceed in checking for matches
                    once found a matching suit or rank
                    when found a match, pop card off and push to either 3rd card or 1st card in that order
                    immediately break bc we only wanna move 1 card at a time
                    and if the stack is empty, you wanna decrease the length because nothing is there!
                */
                if (i >= 3) {
                    if (tempCardCheck[0] == thirdCard[0] || tempCardCheck[1] == thirdCard[1]) {
                        newTop = cardStack[i].pop();
                        cardStack[i - 3].push(newTop);
                        if (cardStack[i].isEmpty()) {
                            stackLength--;
                        }
                        break;
                    }
                    else if (tempCardCheck[0] == firstCard[0] || tempCardCheck[1] == firstCard[1]) {
                        newTop = cardStack[i].pop();
                        cardStack[i - 1].push(newTop);
                        if (cardStack[i].isEmpty()) {
                            stackLength--;
                        }
                        break;
                    }
                }
                else if (tempCardCheck[0] == firstCard[0] || tempCardCheck[1] == firstCard[1]) {
                    newTop = cardStack[i].pop();
                    cardStack[i - 1].push(newTop);
                    if (cardStack[i].isEmpty()) {
                        stackLength--;
                    }
                    break;
                }
                // some debugging, you can ignore this
                if (i == stackLength - 1)
                    done = true;
            }

             // if current stack i is empty 
             // start sliding right to left from index i,
             // to stack length, then want to clear that stack
             // shiftArray() - this will move all stacks to the left that can be moved 
            for (int i = 0; i < stackLength; i++) {

                if (cardStack[i].isEmpty()) {

                    cardStack[i] = cardStack[i + 1];
                    cardStack[i + 1].clearStack();
                }
            }
        }

        // once the whole stack object already iterated, will then output the left stacks
        // revealing what the top card is and how much is in the stack
        if (stackLength > 1) {
            cout << stackLength << " piles remaining => " << endl;
            for (int i = 0; i < stackLength; i++)
            {
                cout << cardStack[i].peek() << ": " << cardStack[i].stackSize() << "  ";
            }
            cout << endl;
        }
        // this is when u win eHEYAAH BOI - basically winning deck will only have 1 pile
        else if (stackLength == 1) {
            // you can assume 52 cards since all in 1 pile
            cout << "Only " << stackLength << " pile with 52 cards with " << cardStack[0].peek() << " card on top" << endl;
        }

        // finally, destroy the stack to restart new data set
        for (int i = 0; i < 52; i++) {
            cardStack[i].clearStack();
        }
     }

    // when all data sets are read though properly close file
    inFile.close();
    // all done! uwu
    return 0;
}

// nomoremoves as a function pass stacklength and mystackArray
// in the function, recheck all cards
// this follows the same logic as above code when finding a matching card
// return false if we reach the complete or if found a move
// only one case return true, iterate through the whole array  
bool noMoreMoves(int stackSize, myStack<string>* stackArray) {
    for (int i = stackSize - 1; i >= 1; i--) {
        string tempCardCheck = stackArray[i].peek();
        string firstCard = stackArray[i - 1].peek();
        string thirdCard;

        if (i > 2) {
            thirdCard = stackArray[i - 3].peek();
        }

        if (i > 2) {
            if (tempCardCheck[0] == thirdCard[0] || tempCardCheck[1] == thirdCard[1]) {
                return false;
            }
            else if (tempCardCheck[0] == firstCard[0] || tempCardCheck[1] == firstCard[1]) {
                return false;
            }
        }
        else if (tempCardCheck[0] == firstCard[0] || tempCardCheck[1] == firstCard[1]) {
            return false;
        }
    }

    return true;
}