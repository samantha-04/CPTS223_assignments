
#include <fstream>
#include <iostream>

using namespace std;

template<typename n, typename p>
class Array
{
private:
n* names;     // Dynamic array for storing names (of type n)
p* points;    // Dynamic array for storing points (of type p)
//Array<n,p>* arr; //dynamic array
int capacity = 100;
int size;


public:

Array(int capacity);
~Array();

void loadProfiles(const std::string& filename);
void addProfile(n name, p points);
int findProfile(string user);
void updatePoints(const n& name, p change);


void displayProfiles() const;
int getSize() const;
int getCapacity() const;
void saveProfiles(const string& filename) ;

};