// This code was taken from https://www.techiedelight.com/queue-implementation-cpp/
// The code has been modified from the original to provide opportunities to learn

/*Poor Attributes
1. Placing everything in a queue.h file works, but I have found that having a .h and .cpp file greatly
aids in organizaion fluidity. 
2. Lack of comments. For example, in the size function, I changed it to return cout becaus to me it made sense that 
count and size were equal. Howver, the original authors idea for the size variable may have been different than mine!
This could've been clarified in a comment. There are several other examples of this throughout.
3. No room for increasing capacity in enqueue(). This is fine, but it could easily utilize dynamic memory and I think it 
would be more efficient to do so. 
4. I'm not sure if this is intended to be in the final implementation of the program, but if it was, having print statements
for each insertion and deletion of queue elements seems redundant and unnecessary. This is what our test cases are for!
5. There's no copy constructor, which works okay with this current program but I can imagine that adding on to this program 
could potentially lead to crashes, especially with our dynamically allocated memory. 
*/
#include <iostream>
#include <cstdlib>
#include <limits>
#include "testQueue.cpp"
using namespace std;

// main function
int main()
{
    // call your test functions here!
    //testSize();
    //testIsEmpty();
    //testIsFull();
    //testDequeueUnderflow();
    //testDequeue();
    //testEnqueueOverflow();
    //testEnqueue();
    //testPeekUnderflow();
    //testPeek();
    return 0;
}

