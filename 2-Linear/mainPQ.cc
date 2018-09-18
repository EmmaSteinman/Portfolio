//===========================================================
// Matt Kretchmar
// mainQ.cc
// April 21, 2017
// A queue testing file
//===========================================================

#include <iostream>
#include "PQueue.h"
using namespace std;



//===========================================================
// main
//===========================================================

int main ( void )
{
    PQueue<char> q1;
    cout << "q1 = " << q1 << endl;
    q1.enqueue('a');
    q1.enqueue('d');
    q1.enqueue('c');
    q1.enqueue('e');
    q1.enqueue('b');
    cout << "q1 = " << q1 << endl;
    
    while ( !q1.isEmpty() )
        cout << "q1 deueue " << q1.dequeue() << endl;
    cout << "q1 = " << q1 << endl;
    
    return 0;
}
