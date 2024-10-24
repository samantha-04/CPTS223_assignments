#include <map>
#include <algorithm> // for max_element
#include "generateUsers.hpp"
using namespace std;


map<string, User> buildMapByUserName(vector<User> users) 
{
    map<string, User> usersMap;

    for (vector<User>::const_iterator itr = users.begin(); itr != users.end(); ++itr) // iterate through the vector
    {
        usersMap[itr->userName] = *itr; // add the user to the map
    }
    return usersMap;

}


map<string, User> buildMapByEmail(vector<User> users) 
{
    map<string, User> emailsMap;
    
    for (vector<User>::const_iterator itr = users.begin(); itr != users.end(); ++itr) // iterate through the vector 
    {
        emailsMap[itr->email] = *itr; // add the user to the map
    }
    return emailsMap;
}


void printMap(map<string, User> aMap) 
{
     for (map<string, User>::const_iterator itr = aMap.begin(); itr != aMap.end(); ++itr) // iterate through the map
     {
        cout << itr->first << ": " << itr->second.firstName << " " << itr->second.lastName << endl; // print the key and the first and last name 
    }
}


bool isMapSorted(map<string, User> aMap) 
{
    map<string, User>::const_iterator prev = aMap.begin();
    for (map<string, User>::const_iterator itr = ++aMap.begin(); itr != aMap.end(); ++itr) // iterate through the map
    {
        if (prev->first > itr->first) // compare keys
        {
            return false;// return 0 if not sorted
        }
        prev = itr; // update prev
    }
    return true; // return 1 if sorted
}


bool testSearchByKey(map<string, User> aMap, string keyToSearch)  
{
    return aMap.find(keyToSearch) != aMap.end(); // return 1 if key exists, 0 otherwise
}


bool testDeleteByKey(map<string, User> aMap, string keyToDelete) 
{
    return aMap.erase(keyToDelete) > 0; // return 1 if key exists, 0 otherwise    
}


void printActiveUsers(map<string, User> aMap) 
{
    int activeThreshold = 800;
    for (map<string, User>::const_iterator itr = aMap.begin(); itr != aMap.end(); ++itr) // iterate through the map
    {
        if (itr->second.numPosts > activeThreshold) // check if the number of posts is greater than the threshold
        {
            cout << itr->first << endl; // print the key 
        }
    }
}


void printMostPopularCategory(map<string, User> aMap) 
{    
    map<string, int> categoryCount;
    for (map<string, User>::const_iterator itr = aMap.begin(); itr != aMap.end(); ++itr) // iterate through the map
    {
        categoryCount[itr->second.mostViewedCategory]++; // increment the count of the category
    }
    
    // find the most popular category
    map<string, int>::iterator mostPopular = max_element(categoryCount.begin(), categoryCount.end(), [](const pair<string, int>& a, const pair<string, int>& b) { return a.second < b.second;});
    cout << mostPopular->first << endl; // print the most popular category
}


int main()
{
    int numUsers = 10;
    vector<User> users = generateUsers(numUsers);


    cout << "Build map with username as key" << endl;
    map<string, User> mapByUserName = buildMapByUserName(users);
    if ( mapByUserName.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;


    cout << "Print \"mapByUserName\" map:" << endl;
    printMap(mapByUserName);
    cout << endl;


    string keyToSearch = "smith55";
    cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByUserName, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    string keyToDelete = "smith55";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByUserName, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    cout << "Test if map's key is sorted" << endl;
    if ( isMapSorted(mapByUserName) )
        cout << "  Order test passed!" << endl << endl;
    else
        cout << "  Order test failed!" << endl << endl;


    cout << "Print usernames with more than 800 tweets:" << endl;
    printActiveUsers(mapByUserName);
    cout << endl;

    cout << "Print the most popular category" << endl;
    printMostPopularCategory(mapByUserName);
    cout << endl;


    cout << " ============================================================================== " << endl << endl;


    cout << "Build map with username as key" << endl;
    map<string, User> mapByEmail = buildMapByEmail(users);
    if ( mapByEmail.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;
    

    keyToSearch = "kat@gmail.com";
    cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByEmail, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    keyToDelete = "kat@gmail.com";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByEmail, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    return 0;
}