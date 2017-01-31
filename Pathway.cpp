//
//  main.cpp
//  Iterative Deepening Search
//
//  Created by Daras Johnson on 1/27/17.
//  Copyright © 2017 Daras Johnson. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

class States { //define a class to hold the nodes and member functions

private:
    struct state1 { //node structures
        char name;  //this will hold the character names for the states (nodes)
        int path;  //this will keep track of the path during the search.
        bool visited; //this will allow me to keep track of stated that have been visited.
        
        //pointers for each node to connect to next and previous nodes
        state1* next;
        state1* prev;
        
    };
    
    //more pointers for member functions to use
    state1* n;
    state1* temp;
    state1* head;
    state1* tail;
    
    //stack to implement my search
    stack<state1*> queue;
    
    
public:
    //Constructor that hard codes the path way for the states
    States() {
        n = new state1;
        n->name = 'D';
        n->prev = NULL;
        head = n;
        tail = n;
        
        n = new state1;
        n->name = 'C';
        n->prev = tail;
        tail->next = n;
        tail = n;
        
        n = new state1;
        n->name = 'B';
        n->prev = tail;
        tail->next = n;
        tail = n;
        
        n = new state1;
        n->name = 'A';
        n->prev = tail;
        tail->next = n;
        tail = n;
        
        n = new state1;
        n->name = 'F';
        n->prev = tail;
        tail->next = n;
        tail = n;
        
        n = new state1;
        n->name = 'E';
        n->prev = tail;
        tail->next = n;
        tail = n;
        tail->next = NULL;
        
    }
    
    //member function that prints out the path way
    void printStatesForward() {
        temp = head; //set temp pointer equal to head or first node in the search
        
        
        //if the path way is going forward, it will execute this if statement
        if (head->path == 2 && temp->visited == true){ //condition: path variable for the node must be 2 and the node must be visited
            while(temp != tail->next) { //while loop to print each node name
                cout << temp->name << " ";
                temp = temp->next;
            }
        }
        //if the path way is going backwards, it will execute this else if statement
        else if (head->path == 1 && temp->visited == true){ //condition: path variable for the node must be 1 and the node must be visited
            while(temp != tail->prev) { //while loop to print each node name
                cout << temp->name << " ";
                temp = temp->prev;
            }
        }
        cout << endl;
        
    }
    
    //this member function sets the head pointer to the desired character
    void setStartState(char a) {
        state1* temp = head;
        
        while(temp->name != a) {
            temp = temp->next;
        }
        
        head = temp;
    }
    
    //this member function executes the search
    void search(char a, char b) {  //function takes the first and last state as parameters
        
        setStartState(a); //member function that sets the start state
        n = head; //sets a pointer equal to the first state
        head->visited = true; //makes the first state visited
        queue.push(n); //pushed that state onto the stack
        
        while(queue.top()->name != b) { //while loop to execute the search. condition: top element of stack does not equal goal
            
            if (queue.top()->name != b){ //if statement. condition: top element does not equal goal state
                
                queue.pop(); //pop the top element off the stack
                
                //now replace that element with it's children nodes
                if (n->next != NULL) { //the element must have a next node or this won't execute
                    temp = n->next;  //points to first child node
                    if (temp->visited != true) { //if that child node has been visited do not place on stack
                        temp->visited = true; //set the child node to visited
                        temp->path = 2; // give it a path of 2
                        queue.push(temp); //push it on the stack
                    }
                }
                //add the second child node
                if (n->prev != NULL) { //if it doesn't have a second child won't execute.
                    temp = n->prev;  //point to second child node
                    if (temp->visited != true ) { //if has been visited do not place on stack
                        temp->visited = true; //set to visited
                        temp->path = 1; //give it a path of 1
                        queue.push(temp); //push it on the stack
                    }
                }
                
                n = queue.top(); //set the current pointer to the top element before the loop repeats
            }
        }
        
        head->path = n->path; //once loop is done, set first pointer path to ending state so it will print out
    }
    void setGoalState() {
        tail = queue.top(); //set tail element equal to top element on stack.
    }
    
};

int main() {
    
    char start, goal, rerun; //declare variables for start and stop state
    States Daras; //create object
    
    do {
    
    //User interactions
    cout << "Start State: ";
    cin >> start;
    cout << "Goal State: ";
    cin >> goal;
    
    
    Daras.setStartState(start);  //set the start state
    Daras.search(start, goal);  //execute search
    Daras.setGoalState();  //set the goal state
    Daras.printStatesForward(); //print the states out
        
        do {
            cout << "Would you like to rerun program? Y or N: ";
            cin >> rerun;
        }while(rerun != 'Y' && rerun != 'N');
        
    }while(rerun == 'Y');
    
    return 0;
}
