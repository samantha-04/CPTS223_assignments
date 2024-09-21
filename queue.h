using namespace std;
// Class for queue

// define default capacity of the queue
#define SIZE 10
class queue
{
    int* arr;		// array to store queue elements
    int capacity;	// maximum capacity of the queue
    int front;		// front points to front element in the queue (if any)
    int rear;		// rear points to last element in the queue
    int count;		// current size of the queue

public:
    queue(int size = SIZE); 	// constructor
    ~queue();   				// destructor

    void dequeue();
    void enqueue(int x);
    int peek();
    int size();
    bool isEmpty();
    bool isFull();
};

// Constructor to initialize queue
queue::queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor to free memory allocated to the queue
queue::~queue()
{
    delete arr; // you are not required to test this function;
    // however, are there issues with it?

    //yes! you would use delete[] arr :)
}

// Utility function to remove front element from the queue
void queue::dequeue()
{
    // check for queue underflow
    if (isEmpty())
    {
        cout << "UnderFlow\nProgram Terminated\n";
        return;
    }

    cout << "Removing " << arr[front] << '\n';

    front = (front + 1) % capacity;
    count--;
}

// Utility function to add an item to the queue
void queue::enqueue(int item)
{
    // check for queue overflow
    if (isFull())
    {
        cout << "OverFlow\nProgram Terminated\n";
        return;
    }

    cout << "Inserting " << item << '\n';

    rear = (rear + 1) % capacity;
    arr[rear] = item; //fixed to insert item
    count++;
}

// Utility function to return front element in the queue
int queue::peek()
{
    if (isEmpty())
    {
        cout << "UnderFlow\nProgram Terminated\n";
        return std::numeric_limits<int>::min();
    }
    return arr[front]; //fixed to return the front of the queue
}

// Utility function to return the size of the queue
int queue::size()
{
    return count; //size and count should be the same 
}

// Utility function to check if the queue is empty or not
bool queue::isEmpty()
{
    return (count == 0); //should check the count since the size doesn't reflect the amount of elements in the array
}

// Utility function to check if the queue is full or not
bool queue::isFull()
{
    return (count == capacity); ///should check the count since the size doesn't reflect the amount of elements in the array
}
