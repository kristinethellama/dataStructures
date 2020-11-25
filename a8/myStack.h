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
#include <cstdlib>

using namespace std;

// class provided by jimi :-)
template <class type >
class myStack
{
public:
	myStack();
	myStack(const myStack < type >&);
	const myStack& operator =(const myStack < type >&);
	~myStack();
	void push(const type&);
	type pop();
	type peek() const;
	bool isEmpty() const;
private:
	type* stack;
	size_t size;
	size_t stackTop;
};

/*
Constructor Name: myStack
Parameters: constructor, none
Return value: constructor, none
Description: sets size to 10 and creates dynamic array filling it with defaults
and also sets the stack top to 0
*/
template<class type>
inline myStack<type>::myStack()
{	
	size = 10;
	stack = new type[size];
	for (size_t i = 0; i < size; i++)
		stack[i] = type();
	stackTop = 0;
}

/*
Constructor Name: myStack
Parameters: myStack copy address 
Return value: constructor, none
Description: deep copy the copy passed param into the lhs mystack object
*/
template<class type>
inline myStack<type>::myStack(const myStack<type>& copy)
{
	// call destructor so no interference
	~myStack();

	// copy the size and capacity
	this->stackTop = copy.stackTop;
	this->size = copy.size;
	// let heapArray be this new copied capacity
	stack = new type[copy.size];

	// deep copy all the elements from our copy into our actual object
	for (int i = 0; i < size; i++)
		stack[i] = copy.stack[i];
}

/*
Function Name: operator=
Parameters: rhs myStack object
Return value: constructor, none
Description: deep copy the rhs passed param into the lhs mystack object
*/
template<class type>
const myStack<type>& myStack<type>::operator=(const myStack<type>& rhs)
{
	if (this != &rhs) {

		// call destructor so no interference
		~myStack();

		// copy the size and capacity
		this->stackTop = rhs.stackTop;
		this->size = rhs.size;
		// let be this new copied capacity
		stack = new type[rhs.size];

		// deep copy all the elements from our copy into our actual object
		for (int i = 0; i < size; i++)
			stack[i] = rhs.stack[i];
	}

	// return our current object
	return *this;
}

/*
Function Name: deconstructor
Parameters: deconstructor, none
Return value: deconstructor, none
Description: deallocates the myStack dynamic array
*/
template<class type>
inline myStack<type>::~myStack()
{
	delete[] stack;
}

/*
Function Name: push()
Parameters: type item address
Return value: none
Description: adds one element onto the stack
*/
template<class type>
inline void myStack<type>::push(const type& item)
{	
	// pushes one element onto to the current stack
	// want to prompt a resize if stacktop == size
	if (stackTop == size) {
		// resize 
		// create a new temp dynamic array
		type* temp;
		size_t oldSize = size;
		// add 10 to new size
		size += 10;
		// allocate temp to new increased size
		temp = new type[size];
		// copy all elements back from heapArr to temp
		for (size_t i = 0; i < stackTop; i++)
			temp[i] = stack[i];

		// deallocate smaller old array
		delete[] stack;
		// stack is now larger
		stack = temp;
		temp = NULL;
	}

	// head insert the item onto the stack top's index
	stack[stackTop] = item;
	// because we now added a new item, increase the index
	stackTop++;
}


/*
Function Name: pop()
Parameters: none
Return value: item type
Description: returns top item of the stack 
and proceeds to delete it if stack is not empty
*/
template<class type>
inline type myStack<type>::pop()
{
	// temportary variable to save the top bc we will be deleting top here
	type saveTop;

	// if stack aint empty
	if (!isEmpty()) {
		// assign the top's value to temp variable
		saveTop = stack[stackTop-1];
		
		// put a default in the top
		stack[stackTop-1] = type();
		// bc we finna delete this, we wanna decrease the top so it goes away
		stackTop--;
		// return the top
		return saveTop;
	}

	// otherwise if empty, return a default
	return type();
}


/*
Function Name: peek()
Parameters: none
Return value: type item 
Description: w/o removing the element, returns the top of stack
*/
template<class type>
inline type myStack<type>::peek() const
{
	// if stack aint 0, return the top item of stack
	if (stackTop != 0) {
		return stack[stackTop-1];
	}
	// otherwise, return default value of type
	else {
		return type();
	}
}


/*
Function Name: isEmpty()
Parameters: none
Return value: true or false
Description: checks the stackTop, if 0, its empty, if not, well its not empty
*/
template<class type>
inline bool myStack<type>::isEmpty() const
{
	// checks to see if stack has no more elements
	// returns true or false depending on if there are contents
	if (stackTop == 0)
		return true;
	return false;
}
