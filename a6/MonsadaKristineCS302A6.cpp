/** Name: Kristine Monsada, 2001381858, Assignment 6*
Description:
    let's make life slightly hard by wanting to build a custom hash class
    through this class, we want to insert words into our hash table in unique indexes so we 
    are able to successfully create a hash table with fastest run time; this is because we have 
    2 tables and 2 hashFunctions which will allow linear probing to be the last method we use
    in the end, every word SHOULD have a unique cubby and we will output that
Input: 
    input01.txt - a file with a buncha random words
    we should be extracting this, and make all words lower case as well as remove any punctuation
Output:
    every unique word found within the txt file as well as the number of occurances that was in the file
*/


#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <unordered_map>
#include "myHash.h"

using namespace std;

int main()
{
    // declared variables
    ifstream inFile;
    string fileName;
    string fileWords = "";
    myHash <string, int> wordCounterHash; // custom hash class
    unordered_map <string, int> wordMappings;  // used for testing purposes
    int totalWords = 0;
    int hashTableCounter = 0;

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

    // begin just reading in the file
    // counting the total word count so i can create a dynamic array to 
    // physically store the words
    while (!inFile.eof()) {
        
        // a break just in case it breaks
        if (inFile.eof())
            break;

        // parse thru, we don't care about this rn tho
        inFile >> fileWords;
        // count how many words in file
        totalWords++;
    }

    // close the file bc we're gonna reopen it again 
    // create the words array which will actually store the words in this time
    string* words = new string[totalWords];
    inFile.close();

    // reopen and clear for any random words
    inFile.open(fileName.c_str());
    fileWords = "";

    // begin loop to read in the words inside the file
    for (int i = 0; i < totalWords; i++) {
        inFile >> fileWords;
        // with each word iteration, want to check the individual letters
        for (size_t j = 0; j < fileWords.length(); j++) {
            // remove any punctuation
            if (fileWords[j] == '.' || fileWords[j] == ',')
                fileWords.erase(j, 1);
            else if (isupper(fileWords[j])) {
            // make any uppercase character to lowercase
                fileWords[j] = tolower(fileWords[j]);
            }
        }
        // now store her inside
        words[i] = fileWords;
    }

    // counts the number of unique words in file
    int entry = 0;
    // holding array to store unique words
    int wordsCapacity = 1000;
    string* wordsArr = new string[wordsCapacity];
    // make sure no garbage is inside
    for (int i = 0; i < wordsCapacity; i++)
        wordsArr[i] = "";

    // now its time to get funky
    // loop to insert each word into our array into our hash table
    // within out hashtable the [] will get the word and search for the same word
    // or insert into a new spot, and basically holds the counts of how many times this word occured
    for (int i = 0; i < totalWords; i++) {
        // sometimes we get a few garbage values but this will prevent that uwu
        if (words[i] != "") {
            // want to insert this unqiue word into an array to it "removes" any duplicate words
            // used mostly for formatting purposes
            // when the counter hash is 0, this signfies the first time seeing that words so we want to save it
            if (wordCounterHash[words[i]] == 0) {
                wordsArr[entry] = words[i];
                // how many words are unique
                entry++;
            }
            // everytime a word is inserted into our hash, we match it to the key
            // or find a new spot for it, then it returns back the address of the counter which we will use l8r
            wordCounterHash[words[i]]++;
        }
        
        //cout << "this is " << words[i] << " occurance: " << wordCounterHash[words[i]]++;
    }

    // ~* woowowo testing purposes *~
    /*
    cout << "lorem: " << wordCounterHash["lorem"] << endl;
    cout << "sit: " << wordCounterHash["sit"] << endl;
    cout << "mauris: " << wordCounterHash["mauris"] << endl;
    cout << "amet: " << wordCounterHash["amet"] << endl;
    cout << "a: " << wordCounterHash["a"] << endl;    
    */

    // output how many unique words
    cout << "Total Entries: " << entry << endl;

    // output that word and the count for each word
    for (int i = 0; i < entry; i++) {
        //cout << wordsArr[i] << " of index " << i << ": " << wordCounterHash[wordsArr[i]] << endl;
        cout << wordsArr[i] << ": " << wordCounterHash[wordsArr[i]] << endl;
    }

    // testing with unordered map to see if my crap works lmao
    /*
    unordered_map<string, int>::iterator p;
    int k = 0;
    for (p = wordMappings.begin(); p != wordMappings.end(); p++) {
        cout << p->first << ": " << p->second << endl;
        k++;
    }   
    cout << "Total words read: " << k << endl;
    */

    // deallocate dynamic arrays
    delete[] words;
    delete[] wordsArr;

    // finally close the file
    inFile.close();
    // ALLLL DONEEEE :-)
    return 0;
}

