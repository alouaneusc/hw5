#ifndef RECCHECK

// For debugging
// #include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
//#include <cstring>

#endif

// using namespace std;


// Add prototypes of helper functions here
void possibleCombinations(std::string in, unsigned int currentIndex, std::string floatingChars, const std::set<std::string>& dict, std::set<std::string>& possibleStrings);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> possibleStrings;
    std::string input = in, floatingChars = floating;
    possibleCombinations(input, 0, floatingChars, dict, possibleStrings);
    return possibleStrings;
}



// Define any helper functions here

void possibleCombinations(std::string in, unsigned int currentIndex, std::string floatingChars, const std::set<std::string>& dict, std::set<std::string>& possibleStrings)
{
    // if the current index is at the end of the string, check if the string is in the dictionary
    if (currentIndex == in.size())
    {

        if (dict.find(in) != dict.end()) possibleStrings.insert(in);
        return;
    }
    // if the current character is not a dash, call possibleCombinations with the next index
    if (in[currentIndex] != '-')
    {
        possibleCombinations(in, currentIndex + 1, floatingChars, dict, possibleStrings);
        return;
    }
    // if the number of dashes is equal to the number of floating characters, replace each dash with a floating character
    if (count(in.begin(), in.end(), '-') == floatingChars.size())
    {
        for (unsigned int j = 0; j < floatingChars.size(); ++j)
        {
            in[currentIndex] = floatingChars[j];
            std::string newfloatingChars = floatingChars;
            newfloatingChars.erase(j, 1);
            possibleCombinations(in, currentIndex + 1, newfloatingChars, dict, possibleStrings);
        }
    }
    else
    {

        for (int j = 0; j < 26; ++j)
        {
            char c = char(j + 97);
            in[currentIndex] = c;
            possibleCombinations(in, currentIndex + 1, floatingChars, dict, possibleStrings);
        }
        for (unsigned int j = 0; j < floatingChars.size(); ++j)
        {
            in[currentIndex] = floatingChars[j];
            std::string newfloatingChars = floatingChars;
            newfloatingChars.erase(j, 1);
            possibleCombinations(in, currentIndex + 1, newfloatingChars, dict, possibleStrings);
        }

    }
}
