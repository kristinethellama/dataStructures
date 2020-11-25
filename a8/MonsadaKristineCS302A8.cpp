/** Name: Kristine Monsada, 2001381858, Assignment 8*
Description:
    oh boy, it's like i'm in elementary school again and i'm playing pick up sticks!
    our pick up sticks will be maintained in an adjacency list where we will iterate thru using depth first search
    in order to detect a cycle, this is necessary because if there is a cycle, there lies dependancies thus as we simulate this game,
    we cannot pick up a stick if it's vulnerable to another stick. that is why we will only display order of what stick COULD be picked with 
    cases that do not have a cycle. once we find a case with no cycle, we create another stack array  to perform a topological sort to
    determine a correct order to remove sticks from the pile of sticks
Input:
    PickUpSticks.txt
    PickThemUpAgain.txt
    OneMoreTime.txt
    text file that contains the number of vertices & the number of edges (the first two nums)
    following the blank line, a whole bunch of numbers where RHS is the node and LHS is where that node will be directed to
    these numbers will be the data that forms our graph
Output:
   IF NO CYCLE
    in each test cast output the order integers, 
    listing the sticks in the order in which they could be picked 
    upwithout ever picking up a stick with another stick on top of it
    (order will be maintained with topological sort when an item will get "removed")
   IF CYCLE
    you really can't pick up sticks bc of this dependency, thus the game is "IMPOSSIBLE"
*/
#include <iostream>
#include <fstream>
#include <string>
#include "myStack.h"
#include "vertex.h"

using namespace std;

// function prototypes of depth first search and topological sort
bool dfs(int, vertex<int>*);
bool dfsHelper(int, bool[], bool*, vertex<int>*);
//void topSort(int, myStack<int>&, vertex<int>*);
//void topSortHelper(int, bool[], myStack<int>&, vertex<int>*);

void topSort(int, myStack<int>&, vertex<int>*, bool*);

int main()
{
    ifstream inFile;
    string fileName;

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

    // graph object
    vertex<int>* pickUpSticks;
    int numVertices, numEdges = 0;
    int sizeOfGraph = 0;
    string tempLine = "";

    // read in graphs edges and vertices
    inFile >> numVertices;
    inFile >> numEdges;

    //cout << "vertices: " << numVertices << endl;
    //cout << "edges: " << numEdges << endl;

    // create the adjacency list for the graph we will store into memory
    pickUpSticks = new vertex<int>[++numVertices];
    // edge & node
    int to = 0;
    int from = 0;

    // loop to read in the numbers in the file
    // we will be creating our graph with this loop
    while (sizeOfGraph < numEdges) {
        if (inFile.eof())
            break;

        // reads in the node
        inFile >> from;
        // where that node points to
        inFile >> to;
        //cout << "from: " << from << endl;
        //cout << "to: " << to << endl;

        // from will be the index we are inserting from
        // to is going to add the value we read doing a head insert to create adj list
        pickUpSticks[from].addEdge(to);
        // iterate threw again
        sizeOfGraph++;
    }

    // create myStack object, will be automatically set as size to be 10
    // we will be using this later with topological sort in order to remove the elements, yet still maintain order
    myStack<int> sortStack;

    /*
        begin depth first search
        this will go call the dfs function and pass our graph and vertices (so we know how much to iterate thru)
        within dfs, we will have a visited array that keeps track of where we've been because just like what jimi says:
        "you take a fork in the road and keep going until you reach a dead end"
        using dfs, we wanna detect there is a cycle or not
        
        A CYCLE IS IN THE GRAPH IFF WE SEE A BACK EDGE DURING DFS

        thus if there IS a cycle, there lies dependencies so we cannot pick up the sticks one by one
        if NO cycle, use topological sort to maintain order as we remove the sticks

        this bool value will determine cycle detection given the test case graph
    */
    bool isCycle = dfs(numVertices, pickUpSticks);

    // cannot pick up sticks if theres a cycle bc dependencies
    if (isCycle) {
        cout << "IMPOSSIBLE! YOU CANNOT WIN!" << endl;
    }
    // u are a winner winner chicken dinner
    // so you CAN pick up the sticks if graph is acyclic
    // thus perform topological sort 
    // to perform a topological sort to determine a correct order to remove sticks from the pile of sticks
    else if (!isCycle) {
        cout << "Excellent.. you have become a master at Pick-Up-Sticks..." << endl;
        // create a visited array to iterate thru
        bool* visitedArr = new bool[numVertices];

        // set this array's elements to false for each index
        int k = 1;
        while (k < numVertices) {
            visitedArr[k] = false;
            k++;
        }

        // call topsort passing in our stack, graph, and visited array
        topSort(1, sortStack, pickUpSticks, visitedArr);

        // time to print out all the elements huhuhu
        // while the stack isnt empty
        while (!sortStack.isEmpty()) {
            // print the top
            cout << sortStack.peek() << endl;
            // remove that element to go to next top
            sortStack.pop();
        }

        // deallocate our visited bc we don't need her anymore
        delete[] visitedArr;
    }

    // deallocate adjacency list
    delete[] pickUpSticks;

    // FILE FRIKIN DONE
    inFile.close();
    // ALL DONE THANK THE UNIVERSE :')
    return 0;
}

/*
Function Name: dfs()
Parameters: # of vertices, the vertex object
Return value: true or false
Description: DFS algorithm
    create the boolean visited and recursive stack arrays to keep track of were we've been
    iterating thru the vertices, recursively call the dfs helper that determines T/F based on cycle detection
    if helper is true, then there is a cycle, if false, no cycle
*/
bool dfs(int numOfVertices, vertex<int>* graph)
{
    // create the visited array and recursive stack to the vertices passed in
    bool* visited = new bool[numOfVertices];
    bool* recursive = new bool[numOfVertices];

    // all of these will be initially set to false
    // with our helper, we set to true to signify we've been inside
    int i = 1;
    while(i < numOfVertices) {
        visited[i] = false;
        recursive[i] = false;
        i++;
    }

    // now that we have all our arrays set up, time to iterate thru each node
    // of the graph and perform DFS
    for (int j = 1; j < numOfVertices; j++) {
        // if at anytime this helper returns true, there is a cycle
        if (dfsHelper(j, visited, recursive, graph)) {
           // deallocate arrays
            delete[] visited;
            delete[] recursive;
            // cycle
            return true;
        }
    }

    // is ascyclic 
    delete[] visited;
    delete[] recursive;
    return false;
}

/*
Function Name: dfsHelper()
Parameters: our current index, boolean visited array, recursive stack, the vertex object
Return value: true or false
Description: DFS algorithm
    create the boolean visited and recursive stack arrays to keep track of were we've been
    iterating thru the vertices, recursively call the dfs helper that determines T/F based on cycle detection
    if helper is true, then there is a cycle, if false, no cycle
    we will use this edge iterator that basically iterates thru our graph starting from the beginning of our graph's index
    and since its a linked list, goes thru the nodes until reaches null
    if our iterator has not been visited yet and helper is true, then we did have a cycle or we already been in the recursive stack also ret true
    otherwise, it is acyclic
*/
bool dfsHelper(int index, bool visited[], bool* recursive, vertex<int>* graph)
{
    // if visited == false bc that means we didn't go into this index yet! 
    if (!visited[index]){
        // now we are entering thus update our visited and recursive so we don't go back and waste time
        visited[index] = true;
        recursive[index] = true;
        
        // using the friend class edge, we will create an iterator so we can properly traverse graph
        vertex<int>::edgeIterator it;
        // start graph from the beginning so we check thru all elements
        it = graph[index].begin();
        while(it != graph[index].end()) {
            /*
                find all the vertices which are not visited and are adjacent to the current node 
                recursively call those neighbors and at anytime that ir returns true, immediately return true
                this means that there is a cycle
            */
            if (!visited[*it] && dfsHelper(*it, visited, recursive, graph))
                return true;
            // adjacent vertices are already marked in the recursion stack, ret true bc been there already
            else if (recursive[*it])
                return true;
            // go to next node
            it++;
        }
    }

    // otherwise, if we went thru the whole graph and we have found no detections of true, meaning all vertices are separate
    // return false
    recursive[index] = false;
    return false;
}

/*
Function Name: topSort()
Parameters: the index, the myStack obj, the vertex object, visited array
Return value: none
Description: topological sort to determine a correct order to remove sticks from the pile of sticks
*/
void topSort(int index, myStack<int>& stack, vertex<int>* graph, bool* visited)
{
    // getting into this index, we set to true as we first enter
    visited[index] = true;

    // first recursively call topological sorting for all its adjacent vertices, then push it to a stack
    vertex<int>::edgeIterator it;
    // looking at the beginning of the graph
    it = graph[index].begin();
    // iterate thru the graph until the end
    while (it != graph[index].end()) {
        // if we didnt go into this index, recursively go thru and we will push element
        if (!visited[*it])
            topSort(*it, stack, graph, visited);
        // next elem
        it++;
    }

    // POOOOSH
    stack.push(index);
}
