/** Name: Kristine Monsada, 2001381858, Assignment 5*
Description: say we're at chuck e cheese and we want to play a plinko game,
    except we're programming the algorithm and a binary tree that simulate the plinko game
    the binary tree is construted by preorder traversal were we pass in the root and the id's are
    assigned 2n and 2n+1 for left and right nodes as well as all flags initially set to false
    with the plinko game, we traverse down through the tree in preorder style, where each node, we
    update the current id and set the nodes flag from false to true which will will have a structure of
    going left THEN right
    this is repeated until C number of trees are done
Input: t.txt, a file that contains C number of trees we will be creating,
    right value is the height of the tree and left value is the number of plinko chips we were passing down
Output: the last leaf node that the last coin lands on
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// binary tree node structure provided by jimi >:)
struct  binTreeNode { 
    int id; 
    bool  flag; 
    binTreeNode* left; 
    binTreeNode* right; 
};

// function prototypes

/** function_identifier:  createBinaryTree
    function that takes in the BT node and the height which will construct the binary tree and set
    its id and flag elements
* parameters: BTN root pointer, height for tree
* return value: none */
void createBinaryTree(binTreeNode*, int);

/** function_identifier:  preorderOutput
    function that takes in the BT node to print out the element id's in preorder traversal
* parameters: BTN root pointer
* return value: none */
void preorderOutput(binTreeNode*);

/** function_identifier:  playPlinko
    function that takes in the BT node and number of coins to construct the playthough of the game
    if false, go left
    if true, go right
    & each traverse will save the current root's id to a variable
* parameters: BTN root pointer, # of "tokens" played
* return value: the final leaf node where the "token" lands */
int playPlinko(binTreeNode*, int);

/** function_identifier:  goodbyeTree
    function that takes in the BT node delete the individual nodes which then destroys the entire tree
    note: i do not support the burning of actual trees :-)
* parameters: BTN root pointer
* return value: none */
void goodbyeTree(binTreeNode*);

int main()
{
    // declared variables
    ifstream inFile;
    string fileName;
    int numOfTrees = 0;
    int treeHeight = 0;
    int tokensInserted = 0;

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

    // how many total trees we will be making,
    // main running counter for the plinko game
    inFile >> numOfTrees;

    while (numOfTrees > 0) {
        // where the token will end up on when games are completed
        int finalSpot = 0;
        // read in right value which signifies the height of the tree
        inFile >> treeHeight;
        // read in left value which signifies how many plinko "games" we will be playing
        inFile >> tokensInserted;

        // creation of the root pointer
        binTreeNode * root;
        // allocate memory to create a new root node
        root = new binTreeNode;

        // set flags where the id will always start at 1 and our root will always be false
        root->flag = false;
        root->id = 1;

        // begin creating the FBT using preorder traversal
        createBinaryTree(root, treeHeight);

        // code to test if trees are created properly
        // preorderOutput(root);

        // we want to keep iterating through the playPlinko recursive function until no more tokens
        // we handle the token decreasing in main rather than in the function for less complications due to
        // recursive function calls
        while (tokensInserted > 0) {
            finalSpot = playPlinko(root, tokensInserted);

            //cout << "this is how many tokens are left: " << tokensInserted << endl;
            // a playthrough has finished
            tokensInserted--;
        }
        cout << "...And the final spot the plinko token lands is: " << finalSpot << endl;
        //cout << finalSpot << endl;

        // reset read in values for next game/tree
        treeHeight = 0;
        tokensInserted = 0;

        // destroys the tree after playing the plinko game
        goodbyeTree(root);
        // we done with tree so move on to next one
        numOfTrees--;
    }

    // successfully close file once everything has been played through
    inFile.close();

    // ALL DONE :-)
    return 0;
}

void createBinaryTree(binTreeNode* r, int height) {
    // we want it to only run up to the correct height allocated which is passed in
    if (height > 0) {
        // create new nodes for our left and right children
        // we will now be able to store values in it shortly
        r->left = new binTreeNode;
        r->right = new binTreeNode;

        // creating an interator pointer so left and right nodes are accessed correctly
        binTreeNode* iter;

        // we point at the currently made left node
        iter = r->left;

        // pattern sequence 1, starting at 1 which is the root,
        // left child's value will always be 2n 
        // also assign left nodes to be false so we will iterate thru plinko correctly
        iter->id = (r->id) * 2;
        iter->flag = false;

        // make sure this current nodes L and R children are NULL so there ain't no garbage up in 'ere
        iter->left = iter->right = NULL;

        // we now point at the right child
        iter = r->right;

        // pattern sequence 2, starting at 1 which is the root,
        // right child's value will always be 2n+1 
        // also assign right nodes to be false so we will iterate thru plinko correctly
        iter->id = ((r->id) * 2) + 1;
        iter->flag = false;

        // make sure L & R children are NULL so no garbage
        iter->left = iter->right = NULL;
        // decrease height because we finished creating a tree level
        height--;

        // recursively make the rest of the tree
        createBinaryTree(r->left, height);
        createBinaryTree(r->right, height);
    }

    return;
}   

void preorderOutput(binTreeNode* r) {
    // standard output to check if my tree has been created correctly
    // will recurse thru tree preorder (top to bottom) & print out the id's of the tree
    if (r != NULL) {
        cout << r->id << endl;
        preorderOutput(r->left);
        preorderOutput(r->right);
    }
    return;
}

int playPlinko(binTreeNode* r, int token)
{
    // like in the game of plinko, we will always be going down the tree
    // variable is assigned to help navigate thru the tree and assign itself to the id element
    // so we have ez access to the leaf/node we are in
    int goDown = r->id;

    // base case at the last node
    // this always should be a leaf & our last element
    if (r->left == NULL && r->right == NULL) {
        return r->id;
    }

    // only want to do it when we got tokens to go down on
    if (token > 0) {
        // we always want to start on the left subtree 
        // thus, if the node's flag is false, we want to traverse left
        if (r->flag == false) {
            // after going down to that root, we set it to true so signify we travsered down
            r->flag = true;
            // assign current id to current left child's id
            goDown = playPlinko(r->left, token);
        }
        // then, after left side traverse, we want to begin right side
        // the trues will help point directions to the right
        else if (r->flag == true) {
            // when we do hit a true node, we want to change it back to false in case more coins
            r->flag = false;
            // again, assign current right child's id
            goDown = playPlinko(r->right, token);
        }
    }

    // we always want to return the last id kept no matter what
    return goDown;
}


void goodbyeTree(binTreeNode* r) {
    // no more tree to traverse
    if (r == NULL) {
        return;
    }

    // recursively iterate thru right and left subtrees
    goodbyeTree(r->left);
    goodbyeTree(r->right);

    // we will delete this node's contents and itself, completely destroying the tree
    // cout << "this is what is going away: " << r->id << endl;
    delete r;
}