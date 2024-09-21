#include <iostream>
#include "testQueue.h"
#include "queue.h"
#include <limits>
/* Test ID: Size Check - SC
Unit: queue::size ()
Description: test to determine if queue::size() returns 0 if the count is zero
Test steps:
1. Initialize a new queue
2. Invoke queue::size()
3. Conditionally evaluate the value returned by queue::size()
Test data: count = 0
Precondition: size is 0
Postcondition: size is 0
Expected result: size is 0
Actual result: size is 1 
Status: failed
*/
void testSize()
{
    queue queue(0);
    cout << "Queue size: " << queue.size() << endl;

}

/* Test ID: Empty queue check - EQC
Unit: queue::isEmpty ()
Description: test to determine if queue::isEmpty () returns 1 if a queue object
is empty.
Test steps:
1. Construct an empty queue object
2. Invoke queue::isEmpty ()
3. Conditionally evaluate the value returned by queue::isEmpty ()
Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty
Expected result: queue is empty; 1 is returned
Actual result: queue is NOT empty; 0 is returned
Status: failed
*/

void testIsEmpty()
{
    queue queue(0);

    if (queue.isEmpty())
    {
        cout << queue.isEmpty() << endl;
        cout << "Queue is empty!" << endl;
    }

    else
    {
        cout <<queue.isEmpty() << endl;
        cout << "Queue not empty!" << endl;
    }
    

}

/* Test ID: Full queue check - FQC
Unit: queue::isFull ()
Description: test to determine if queue::isFull() returns 1 if a queue object
is full.
Test steps:
1. Construct an populated queue object
2. Invoke queue::isFull ()
3. Conditionally evaluate the value returned by queue::isFull ()
Test data: size = 5
Precondition: queue object is full
Postcondition: queue object is still full
Expected result: queue is full; 1 is returned
Actual result: queue is full; 1 is returned
Status: passed
*/

void testIsFull()
{
        queue queue(3);
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);

    if (queue.isFull())
    {
        cout << queue.isFull() << endl;
        cout << "Queue is full!" << endl;
    }

    else
    {
        cout <<queue.isFull() << endl;
        cout << "Queue not full!" << endl;
    }
}


/* Test ID: dequeue underflow check - DUC
Unit: queue::dequeue ()
Description: test to determine if queue::dequeue() prints "UnderFlow\nProgram Terminated\n" if a queue is 
empty while attempting to dequeue, and terminates program. 
steps:
1. Construct an empty queue
2. Invoke queue::dequeue ()
3. Observe statement returned by queue::dequeue ()
Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty, program ends
Expected result: queue is empty; program terminated
Actual result: queue is empty; "Removing 0/ floating point exception"
Status: failed
*/
void testDequeueUnderflow()
{
    queue queue(0);
    queue.dequeue();
}

/* Test ID: dequeue check - DC
Unit: queue::dequeue ()
Description: test to determine if queue::dequeue() successfully removes the front element of queue
steps:
1. Construct a populated queue
2. Invoke queue::dequeue ()
3. Observe front element and size of queue
Test data: size = 4
Precondition: queue size = 4 (count = 3)
Postcondition: queue size = 3 (count = 2)
Expected result: front element of queue removed
Actual result: rear element of queue removed
Status: failed
*/
void testDequeue()
{
    queue queue(4);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    queue.dequeue();

    cout << "Expected size: 3\nActual size: " << queue.size() << endl;
    cout << "Expected front: 2\nActual front: " << queue.peek();

}

/* Test ID: enqueue overflow check - EOC
Unit: queue::enqueue ()
Description: test to determine if queue::enqueue() prints "OverFlow\nProgram Terminated\n" if a queue is 
full while attempting to enqueue, and terminates program. 
steps:
1. Construct a full queue
2. Invoke queue::enqueue ()
3. Observe statement returned by queue::enqueue ()
Test data: size = 3
Precondition: queue object is full
Postcondition: queue object is still full, program ends
Expected result: queue is full; program terminated
Actual result: queue is full, program terminated
Status: passed
*/
void testEnqueueOverflow()
{
    queue queue(3);

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    queue.enqueue(4); //overflow
}

/* Test ID: enqueue check - EC
Unit: queue::enqueue ()
Description: test to determine if queue::enqueue() successfully adds element to front of queue
1. Construct an empty queue
2. Invoke queue::enqueue ()
3. Observe front element and size of queue
Test data: size = 3
Precondition: queue is empty
Postcondition: queue has three elements
Expected result: each element is added to front of queue
Actual result: SIZE was added to front of queue
Status: failed
*/
void testEnqueue()
{
    queue queue(3);

    queue.enqueue(10);
    cout << "Front element: " << queue.peek() << endl;

    queue.enqueue(20);
    cout << "Front element: " << queue.peek() << endl;

    queue.enqueue(30);
    cout << "Front element: " << queue.peek() << endl;

}

/* Test ID: peel underflow check - PUC
Unit: queue::peek ()
Description: test to determine if queue::peek() prints "UnderFlow\nProgram Terminated\n" if a queue is 
empty while attempting to peek, and terminates program. 
steps:
1. Construct an empty queue
2. Invoke queue::peek ()
3. Observe statement returned by queue::peek()
Test data: size = 0
Precondition: queue object is empty
Postcondition: queue object is still empty, program ends
Expected result: queue is empty; program terminated
Actual result: queue is empty; program did not correctly terminate
Status: failed
*/
void testPeekUnderflow()
{
    queue queue(0);

    int front = queue.peek();  
    
    //check if the returned value is correct
    if (front == std::numeric_limits<int>::min()) 
    {
        cout << "Test passed: Peek returned the correct value." << endl;
    } 
    else 
    {
        cout << "Test failed: Peek did not return the correct value." << endl;
    }
}

/* Test ID: peek check - PC
Unit: queue::peek ()
Description: test to determine if queue::peek() successfully returns front element of queue
1. Construct a populated queue
2. Invoke queue::peek ()
3. Observe front element of queue
Test data: size = 3
Precondition: queue is empty
Postcondition: queue has three elements
Expected result: front element is 1
Actual result: front element is 3
Status: failed
*/
void testPeek()
{
    queue queue(3);

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    cout << "The expected front element is 1.\nThe actual front element is: " << queue.peek();

}
