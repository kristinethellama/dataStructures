/** Name: Kristine Monsada, 2001381858, Assignment 2*
Description: using insertion sort and inversion counter to sort DNA
    strands to most sorted to least sorted
Input: A12nput.txt, a file that contains the data strands of the size of 
    the data sets and the actual dna strings
    this is in unsorted order atm
Output: all datasets to be sorted from most sorted to least sorted without 
    actually sorting the individual characters
     WE ARE SORTING BY STRINGS BASED ON INVERSIONS! */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	// declared variables
    // area for all declared variables
    ifstream inFile;
    string fileName;
    int numOfStrings = 0;
    int lengthOfStrings = 0;
    int numOfDataSet = 0;
    string holder = "";

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

    // read in the total datasets in txt file
    inFile >> numOfDataSet;

    // this is so it keeps running and going through all the data sets
    while (numOfDataSet > 0) {
        
        // read in string length and the number of indexes we will have
        inFile >> lengthOfStrings;
        inFile >> numOfStrings;
        
        // dynamic array creation of the new string array
        string* dnaArray = new string[numOfStrings];

        // read in value and then assign it
        for (int i = 0; i < numOfStrings; i++) {
            inFile >> holder;
            // stores entire string into array
            dnaArray[i] = holder;

        }


        // begin block of code where we find the number of inversions on individual string
        char currentChar, nextChar;
        int inversionCounter = 0;
        // we will store our inverted counts into another array
        // this is to link our dna array so we can do the correct swaps
        int* inversionArray = new int[numOfStrings];

        // begin counting the # of inversions read
        /*
          how it works is because it is stored into a string array, each
          character is its own mini-index so this mimics a faux-2d array
          we get the into the current i's index and then j's character index
          to store in a character variable where we use to compare
          it then takes the next character and loops to see if our current character is 
          larger (using ascii), if larger, count inversions
          once all accounted for, will store into the inversion array
          we want to link this up for our insertion sort
        */
        for (int i = 0; i < numOfStrings; i++) {
            // to reset each time
            inversionCounter = 0;
            for (int j = 0; j < lengthOfStrings - 1; j++) {
                currentChar = dnaArray[i][j];
                for (int k = j + 1; k < lengthOfStrings; k++) {
                    nextChar = dnaArray[i][k];
                    if (currentChar > nextChar) {
                        // increases whenever the current character is higher on the alphabet
                        inversionCounter++;
                    }
                }
            }

            inversionArray[i] = inversionCounter;
        }


        // insertionSort() algorithm
        // we have 2 keys, one for the inversion count array and the regular string array
        // so it links up and accurately shifts both to get correct sortedness
        int j, key;
        string dnaKey = "";
        for (int i = 1; i <= numOfStrings - 1; i++) {
            // we want to set keys to the 2nd element
            // this is what we are comparing with
            key = inversionArray[i];
            dnaKey = dnaArray[i];

            // and compare it to the one before
            // kind of read as if i-1 is greater than i, swap because
            // at the end most sorted should make its way to the front and least to back
            // if j is larger, it will keep shifting until at correct spot
            for (j = i - 1; j >= 0 && inversionArray[j] > key; j--) {
                // begin swapping to move elements down
                dnaArray[j + 1] = dnaArray[j];
                inversionArray[j + 1] = inversionArray[j];
            }
            // update key so we can check for any new swaps
            inversionArray[j + 1] = key;
            dnaArray[j+1] = dnaKey;
        }

        // displays sorted array
        cout << "Begin sorting DNA sequences from most to least sorted ... : " << endl;
        for (int i = 0; i < numOfStrings; i++) {
            cout << dnaArray[i] << endl;
        }
        cout << endl;

        // move on to next set
        numOfDataSet--;

        // deallocate
        delete[] dnaArray;
        delete[] inversionArray;

        // make sure pointers aren't pointing to garbage
        dnaArray = NULL;
        inversionArray = NULL;
    }

    // sucessfully closed when all done
    inFile.close();
    // alll done!! :-)
    return 0;
}