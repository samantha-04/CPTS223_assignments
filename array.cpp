#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "array.h"

using namespace std;

//constructor
template<typename n, typename p>
Array<n,p>::Array(int capacity)
{
    this->capacity = capacity;
    this->size = 0;
    names = new n[capacity];
    points = new p[capacity];
}

//destructor
template<typename n, typename p>
Array<n,p>::~Array()
{
    delete []names;
    delete []points;
}

template <typename n, typename p>
void Array<n, p>::loadProfiles(const std::string& filename)
{
    ifstream file(filename);
        
        if (!file.is_open()) 
        {
            cerr << "Error: Could not open " << filename << endl;
            return;
        }

        string line;
        
   
        while (getline(file, line) && size < capacity) 
        {
            //stringstream alows for easy parsing by reading the name, stopping at the comma, 
            //and then storing everything after the comma as points
            stringstream ss(line);
            n name;
            p points;

            //read line
            if (getline(ss, name, ',') && ss >> points) 
            {
                addProfile(name, points);
            } 
            else 
            {
                cerr << "Error: line formatting unrecognized in " << filename << endl;
            }
        }

        file.close();
   
}
template <typename n, typename p>
void Array<n, p>::addProfile(n name, p point)
{
    if (size < capacity) {
            names[size] = name;
            points[size] = point;
            size++;
        } else {
            cerr << "Array is full. Cannot add more profiles." << endl;
        }
}
template <typename n, typename p>
int Array<n, p>::findProfile(string user)
{
    for(int i = 0; i <= size; i++)
    {
        if (user == names[i])
        {
            return points[i];
        }
    }

    cerr << "Profile not found" << endl;
    return 0;
}
template <typename n, typename p>
void Array<n, p>::updatePoints(const n &name, p change)
{
    for (int i = 0; i < size; i++) 
    {
        if (names[i] == name) 
        {  
            points[i] += change;  //modify points
            return;
        }
    }
}

template <typename n, typename p>
void Array<n, p>::saveProfiles(const string &filename) 
{
       ofstream file(filename);

    //check if the file opened successfully
    if (!file.is_open()) 
    {
        cerr << "Error: Could not open " << filename << " for writing." << endl;
        return;
    }

    //loop through each profile and write the name and points to the file
    for (int i = 0; i < size; i++) 
    {
        file << names[i] << "," << points[i] << endl;  //write name and score
    }

    file.close();  //close the file after writing
}


template <typename n, typename p>
void Array<n,p>::displayProfiles() const 
{
    for (int i = 0; i < size; i++) 
    {
        cout << "Name: " << names[i] << ", Points: " << points[i] << endl;
    }
}

//function to get the size of the array
template <typename n, typename p>
int Array<n,p>::getSize() const 
{
    return size;
}

//function to get the capacity of the array
template <typename n, typename p>
int Array<n,p>::getCapacity() const 
{
    return capacity;
}

