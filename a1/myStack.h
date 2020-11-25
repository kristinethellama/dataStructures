/** Name: Kristine Monsada, 2001381858, Assignment 1*
Description: a type of solitare game called "accordions"
	cards will be pushed on to stacks based on matching
	ranks or suits until no more moves can be made or 1 stack left
Input: A1input.txt, a file that contains data of 2 sets of 52 cards
	program will finish reading until "#" sign/eof*
Output: the number of piles of stacks with the top of the stack revealed
	as well as how many cards are in each stack */

// header file of assignment 1

#include <cstdlib>
#include <iostream>
using namespace std;

/** class_identifier: 
	myStack templated object class, basically creates stacks in the form of a linked list
constructors: 
	myStack() - default constructor, sets everything to NULL or zero
	myStack(copy) - copy constructor, will take stack passed in and deep copy it
	~myStack() - destructor, dealloctaes the stack
public functions: a vertical list of public function prototypes
	const myStack& operator=(const myStack<type>&) - overloaded assignment operator, assists to copy rhs to lhs
	void clearStack(); - destroys stack
	void push(const type&); - pushes 1 element onto stack
	type peek() const; - returns top of stack
	type pop(); - returns top of stack and removes it afterwards
	bool isEmpty() const; - checks if the stack has no current elements
	int stackSize() const; - returns the stack size which is manipulated in push/pop
static members: a vertical list of any static members                
	node struct - link & item used to access items and next elements
	size - stack counter
	stackTop - the top of the stack
(variables and function prototypes)**/

template <class type>
class myStack
{
public:
	myStack();
	myStack(const myStack<type>&);
	~myStack();
	const myStack& operator=(const myStack<type>&);
	void clearStack();
	void push(const type&);
	type peek() const;
	type pop();
	bool isEmpty() const;
	int stackSize() const;
private:
	struct node
	{
		type item;
		node* link;
	};

	int size;
	node* stackTop;
};

// default constructor, initializes empty stack
template <class type>
myStack<type>::myStack()
{
	// this will set head to null :-), which initializes the empty stack
	// makes size 0 so no garbage value there
	stackTop = NULL;
	size = 0;
}

// performs deep copy of the stack
template <class type>
myStack<type>::myStack(const myStack<type>& copy)
{
	// points to current element
	node* curr;
	// points to next element from curr in stack
	node* next;
	// assists next in order to get elements pointing correctly
	node* temp;

	// iterates through linked list if stack has items
	// pops off items
	if (stackTop != NULL) {
		while (stackTop != NULL) {
			temp = stackTop;
			stackTop = stackTop->link;
			delete temp;
		}
	}

	// will not copy if head points to NULL (signifying the end)
	if (copy.stackTop == NULL)
		stackTop = NULL;
	else {
		// sets the current node to the copy stack
		curr = copy.stackTop;
		// a new front is created for the copy
		stackTop = new node;
		// copies all the values from the current and copuy head
		stackTop->item = curr->item;
		// wants to set to NULL if it reaches the end so no dangling ptr
		stackTop->link = NULL;
		// last node is now head
		next = stackTop;
		// wanting to point to itself so it all connects
		curr = curr->link;
	}

	// continues to copy the item and link it until 
	// the current node has reached the end (NULL)
	while (curr != NULL) {
		// it will copy the items and links onto node
		// it will be able to copy by tracking everything with current & last
		node* i = new node;
		// copies the element
		i->item = curr->item;
		i->link = NULL;
		next->link = i;
		next = i;
		// moves to next node
		curr = curr->link;
	}

}

// destructor, will deallocate the stack
template <class type>
myStack<type>::~myStack()
{
	// calls clearStack() because they are both doing the same thing
	clearStack();
}

// assignment operator, copies rhs to lhs on an object type
template <class type>
const myStack<type>& myStack<type>::operator=(const myStack<type>& rhs)
{
	// if current object is not equal to the rhs of assignment
	// it will then use the copy constuctor to make element and 
	// then returns back to object, signifies a succesful copy
	if (this != &rhs) {
		// we want to make sure this is all empty before proceeding
		clearStack();
		// make a temporary node of stackPassed in where it is its top
		node* temp = rhs.stackTop;
		// create a stackObject so we will use to push the passed in items
		myStack <type> tempStack;
		while (temp != NULL) {
			// continues to push in everything until no more items left
			tempStack.push(temp->item);
			temp = temp->link;
		}
		// time since everything is now in temp stack, time to push it onto lhs
		while (!tempStack.isEmpty()) {
			push(tempStack.pop());
		}
	}

	// returns that new deep copy stack
	// which is lhs
	return *this;
}

// pushes one element onto to the current stack
template <class type>
void myStack<type>::push(const type& element)
{
	// node to insert a new item on stack
	// used in collapsing cards to a bigger stack
	node* newInsert;
	newInsert = new node;
	// new pointer will point to new element passed in
	newInsert->item = element;
	// will then attach itself as the top of stack
	newInsert->link = stackTop;
	stackTop = newInsert;

	// prevents dangling ptr
	newInsert = NULL;

	// counter for stack size
	size++;
}

// returns the top of the stack in templated type form
template <class type>
type myStack<type>::peek() const
{
	// will execute if there is card on stack
	if (stackTop != NULL) {
		// returns the topmost card
		return stackTop->item;
	}
	else {
		// if nothing, returns a default value
		return type();
	}
}

// saves the top into a temp var
// pops off the element in the stack, which will remove current element
// returns the top
template <class type>
type myStack<type>::pop()
{
	node* temp;
	type saveTop;

	// removes the top element
	if (!isEmpty()) {
		// returns the top of the item
		// using the temp its able to get the linked iteme
		// and remove it to "pop"
		saveTop = stackTop->item;

		temp = stackTop;
		// moves to next node
		stackTop = stackTop->link;
		delete temp;
		// stack size decreased since value gone
		size--;

	}
	// top item of stack
	return saveTop;

}

// checks to see if stack has no more elements
// returns true or false depending on if there are contents
template <class type>
bool myStack<type>::isEmpty() const
{
	// head == NULL will always return true
	// if not will be false
	return (stackTop == NULL);

}

// returns stack size which was changed throughout push and popping
template <class type>
int myStack<type>::stackSize() const
{
	// this will return the size of the current stack
	return size;
}

// will be used with the destructor
// basically destroys the entire stack and prevents any mem leaks from
// occuring through the code
template <class type>
void myStack<type>::clearStack()
{
	// used to deallocate everything in the linked list stack
	// this will prevent any garbage/dangling pointers from happening
	while (!isEmpty()) {
		// uses pop because it will just deallocate everything since pop off stack
		pop();
	}
	// set this to null when done so it isn't pointing at some garbage
	stackTop = NULL;
	return;
}

#pragma once
