/** Name: Kristine Monsada, 2001381858, Assignment 4*
Description: using threads to multiply matricies in parallel!!
Input: matrix.txt, a file that contains 2 matricies, before each matrix, 
    it shows their row and column size so it correctly forms the vector
Output: a new n x n matrix, that shows the multiplied matrices together
     */

#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// globally declared 2d vectors
vector<vector<int>> matrix1;
vector<vector<int>> matrix2;
vector<vector<int>> result;

// function prototype
/** function_identifier:  matrixMultiplication
    function that take in the current row index, column index, 
    and "shared" value between 2 matrices
    iterates though the row of matrix 1 and column of matrix 2 and multiplies together,
    finally doing a summation of those into the result 2d vector
* parameters: current row index, current column index, shared dimension between matrix 1 and 2
* return value: none */
void matrixMultiplication(const int,const int, const int);

int main()
{
    // declared variables
    vector<thread> threadPool;
    int maxThreads = thread::hardware_concurrency();
    ifstream inFile;
    string fileName;
    int matrixRow = 0;
    int matrixCol = 0;
    int matrixElements = 0;

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

    // read in the dimensions of the matrix 1
    inFile >> matrixRow;
    inFile >> matrixCol;

    // this will create the 1 row of 10
    matrix1.resize(matrixRow);

    // forms the 2d array and adds the columns of 5 to the 10 rows
    for (int i = 0; i < matrix1.size(); i++)
        matrix1[i].resize(matrixCol);

    // read in value
    // populate vector with elements inside txt file
    for (int i = 0; i < matrixRow; i++) {
        for (int j = 0; j < matrixCol; j++) {
            inFile >> matrixElements;

            matrix1[i][j] = matrixElements;

            //cout << matrix1[i][j] << " ";
        }
        // cout << endl;
    }

    // clear out, we gonna read in the next matrix
    matrixRow = 0;
    matrixCol = 0;

    // read in the dimensions of the matrix 2
    inFile >> matrixRow;
    inFile >> matrixCol;

    // declare a 2d vector with read in matrix row and col values
    matrix2.resize(matrixRow);

    // reads in columns and this will grow into 2d matrix
    for (int i = 0; i < matrix2.size(); i++)
        matrix2[i].resize(matrixCol);

    //cout << endl;

    // populate vector with elements inside txt file
    // saves the read in element into the specified indexed array
    for (int i = 0; i < matrixRow; i++) {
        for (int j = 0; j < matrixCol; j++) {
            inFile >> matrixElements;

            matrix2[i][j] = matrixElements;

            // cout << matrix2[i][j] << " ";
        }
        // cout << endl;
    }

    // cout << "This is matrix 1 size: " << matrix1.size() << endl;
    // cout << "This is matrix 2 size: " << matrix2.size() << endl;
    //cout << "This is matrix 2 size column: " << matrix2[0].size() << endl;

    // continue the same process of matrix1 and matrix2
    // we take the row size of matrix 1
    result.resize(matrix1.size());

    // we take the column size of matrix 2
    for (int i = 0; i < result.size(); i++)
        result[i].resize(matrix2[0].size());

    // cout << "This is our product matrix size: " << result.size() << endl;

    // initialize result matrix to 0
    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix2[0].size(); j++) {
            result[i][j] = 0;

            // cout << result[i][j] << " ";
        }
        // cout << endl;
    }

    // begin threading 
    // this was used from jimi's threadPool.cpp example to link up the threads for for this assignment :))
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            //spawn a thread to compute matrix multiplication of the 2 matrices
            // i pass in the row index of i and j index of column, as well as the shared value of 
            // the two matrices, m x n to n x m where n is the shared value
            // these threads will go into the function anc calculate matrix multiplication in parallel
            threadPool.push_back(thread(matrixMultiplication, i, j, matrix2.size()));

            //if we spawned the max amount of threads that this system can handle
            //we wait for all of them to finish before we spawn more threads
            if (threadPool.size() == maxThreads)
            {
                for (int k = 0; k < threadPool.size(); k++)
                    threadPool[k].join();

                //wipe out the threadPool after all the threads are done runnning
                threadPool.clear(); 
            }
        }
    }

    // wait for any leftover threads that were spawned in the above loop before continuing
        for (int i = 0; i < threadPool.size(); i++)
            threadPool[i].join();

    //wipe out the threadPool after all the threads are done runnning
    threadPool.clear();

    // print results of the multiplied matrix
    // in nicely formatted output 
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            cout << left << setw(7) << left << result[i][j] << " ";
        }
        cout << endl;
    }

    // clear up all vectors
    matrix1.clear();
    matrix2.clear();
    result.clear();

    // all done multiplying so properly close txt file!
    inFile.close();

    // we DUN hereeee :-)
    return 0;
}


// only need the row index of A (matrix1), and col index of B (matrix2)
void matrixMultiplication(const int rowIndex, const int colIndex, const int sharedSize) {
    
        // because we're given the row index, we only want to iterate through columns 
        // since shared value is what would give us the correct dimensions of new result array
        for (int j = 0; j < sharedSize; j++) {
            
            /*cout << "this is j: " << j << endl;

            cout << "(1) " << matrix1[rowIndex][j] << " ";
            cout << "(2) " << matrix2[j][colIndex] << endl;
            */

            // this will multiply the specific indexes of matrix1 and matrix2 then we do a summation 
            // through the rules of matrix multiplication
            // we only want to multply the corresponding rows and colums and just iterate through those given parameters
            // which j does and we store them into the alotted slot of the result matrix through our parameters as the correct 
            // products within the matrix
            result[rowIndex][colIndex] += matrix1[rowIndex][j] * matrix2[j][colIndex];
        }
    return;
}