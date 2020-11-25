/** Name: Kristine Monsada, 2001381858, Assignment 7*
Description:
    the horrid day comes: *registration day*, students are savages and they all want to get into the same class
    HOWEVER, depending on your registration day, you might not get into the class you want (or worse have to take the bad professor)
    the student is usain bolt, with a few extra caveats: you DO wanna be the person who enrolls earliest but sometimes your gpa, status,
    and drop class count DOES matter in order for you to get in
    getting thru the students, we maintain these checks thru a priority queue built with a binary MIN heap
    this heap will insert the students to the back of the array, then bubble up accordingly so its in the correct spot
    once we have all the students inside the heap, THE RACE IS ON!
    evaluate the heap by checking students enrollment day, gpa, status, and drop
    people that enrolled first get priority over others and then check for the rest
    program should display students to got into the class, students that are waitlisted, and students that didn't make it (RIP)
Input:
    enrollment.txt, contains the maximun enrollment capacity and the maximum waitlist capacity
    following, has all the student names and their enrollment day, gpa, status (F,SP,J,SR), and # of drops in this order
Output:
    all these students from most priority to least priority on:
    who got into the class
    who got waitlisted
    who got rejected
*/

#include <iostream>
#include <fstream>
#include <string>
#include "binMinHeap.h"

using namespace std;

// studentType struct which is gonna be what our heap uses

/*
    algorithm for operator<
    (a)  If student 1 enrolled at least one day before student 2
    (b)  If student 1 and student 2 enrolled on the same day, 
            then if student 1 is an upper classman over student2 then student 1 has the priority
    (c)  If student 1 and student 2 enrolled on the same day and they are the same class, 
            then student 1 has priority of student 2 if student 1’s gpa is higher and student 1 dropped few times
*/

struct  studentType {
    string  name; 
    double  gpa; 
    int status, droppedCount, dayEnrolled;
    //You  will  need to  overload  one of  these  for  the  priority  queue
    /*
    Function Name: operator<
    Parameters: studentType address
    Return value: returns true or false
    Description: compares the element values in the studentType object to determine priority
    */
    bool  operator <(const  studentType& student2) const {
        if (this->dayEnrolled < student2.dayEnrolled)
            return true;

        else if (this->dayEnrolled == student2.dayEnrolled) {
            if (this->status > student2.status)
                return true;

            if (this->status == student2.status) {
                
                if (this->gpa > student2.gpa && this->droppedCount < student2.droppedCount)
                    return true;
            }
        }

        return false;
    };
    /*
    Function Name: operator>
    Parameters: studentType address
    Return value: returns true or false
    Description: compares the element values in the studentType object to determine priority
    */
    bool  operator >(const  studentType& student2) const {
        if (this->dayEnrolled < student2.dayEnrolled)
            return true;

        else if (this->dayEnrolled == student2.dayEnrolled) {
            if (this->status > student2.status)
                return true;

            if (this->status == student2.status) {
                if (this->gpa > student2.gpa && this->droppedCount < student2.droppedCount)
                    return true;
            }
        }

        return false;
    };
}; 

int main()
{   
    ifstream inFile;
    string fileName;
    int enrollmentCapacity = 0;
    int waitlistSize = 0;
    int studentAmount = 0;

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

    // temp studentType object which we will read into
    // we will also be using this to hold the name as we output the results uwu
    studentType students;
    // string to get the line
    string studentInfo = "";

    // read in the enrollment capacity for the size
    // read in the waitlist capacity
    inFile >> enrollmentCapacity;
    inFile >> waitlistSize;

    // we are just reading in to get the counter
    while (getline(inFile, studentInfo, '\n')) {
        studentAmount++;
    };

    // close for now
    inFile.close();
    
    // cout << studentAmount << endl;

    // reopen bc now we're reading forrealsies
    inFile.open(fileName.c_str());

    // reset
    enrollmentCapacity = 0;
    waitlistSize = 0;

    // read in the enrollment capacity for the size
    // read in the waitlist capacity
    inFile >> enrollmentCapacity;
    inFile >> waitlistSize;

    //cout << enrollmentCapacity << endl;
    //cout << waitlistSize << endl;

    // out min heap to keep track of the priority of students
    binMinHeap<studentType> listOfStudents(studentAmount);
    int counter = 0;
    studentInfo = "";
    // get one line from this file
    while (counter < studentAmount) {

        // retrieve 1 line
        getline(inFile, studentInfo, '\n');
       // if it reaches the end, break out - we read everything
        if (inFile.eof())
            break;

        // b/c we used getline, we can extract the individual elements
        // read in students name, dayEnrolled, gpa, status, drop class count
        inFile >> students.name;
        inFile >> students.dayEnrolled;
        inFile >> students.gpa;
        inFile >> students.status;
        inFile >> students.droppedCount;

        // shove into the heap array
        listOfStudents.insert(students);
        counter++;
    }

    /*
        begin to display the priority queue!
        from the binary min heap, the first student has the most priority 
        then trickles down to student with the least priority
        to determine priority, we think less/min so if student1 enrolled earlier than student2
        then we move on to the next priority, where we focus on if students are upper/lower classmen
        clearly, upper classmen have priority BUT, if same class, then we check which student has the 
        better gpa and least dropped

        we start off by looping thru & displaying the students who got in
        following looping thru & displaying the waitlisted students
        and finally displaying the students who for sure didn't get into the class
    */
    cout << "Lucky duck students (Successfully enrolled)" << endl;
    cout << "-----------------------------------------------------------" << endl;

    // highest priority for students who got into the class
    for (int i = 0; i < enrollmentCapacity; i++) {
        // get the minimum bc this is the most priority
        students = listOfStudents.getMin();
        // now that we have the min, we can take it off and then bubbleDown everything
        listOfStudents.deleteMin(); 
        // display thy student's name
        cout << students.name << endl;
    }

    cout << endl;
    cout << "You miiight get in, but we all know what your fate is (Waitlisted)" << endl;
    cout << "-----------------------------------------------------------" << endl;

    // highest priority for students who got waitlisted
    for (int i = 0; i < waitlistSize; i++) {
        // get the minimum bc this is the most priority
        students = listOfStudents.getMin();
        // now that we have the min, we can take it off and then bubbleDown everything
        listOfStudents.deleteMin();
        // display thy student's name and what position of getting in they are in b/c that matters irl
        cout << "#" << i+1 << " " << students.name << endl;
    }

    cout << endl;
    cout << "Better luck next semester :/ (Rejected)" << endl;
    cout << "-----------------------------------------------------------" << endl;
    // highest priority for students who got rejected (so sadly not rly priority)
    while (!listOfStudents.isEmpty()) {
        // get the minimum bc this is the most priority
        students = listOfStudents.getMin();
        // now that we have the min, we can take it off and then bubbleDown everything
        listOfStudents.deleteMin();
        // display thy student's name
        cout << students.name << endl;
    }

    // close zee file
    inFile.close();

    // get er done 
    return 0;
}