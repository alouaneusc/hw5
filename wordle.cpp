// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
//#include <cstring>
using namespace std;


// Add prototypes of helper functions here

void charCombiner(std::string in, unsigned int currentIndex, std::string floatingCopy, const std::set<std::string>& dict, std::set<std::string>& answers);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
	std::set<std::string> validWords;

	std::string input = in;
	std::string floatingChars = floating;
	charCombiner(input, 0, floatingChars, dict, validWords);
	return validWords;
}

// Define any helper functions here

void charCombiner(std::string in, unsigned int currentIndex, std::string floatingCopy, const std::set<std::string>& dict, std::set<std::string>& answers)
{
	unsigned int count = 0;
	char character;
	for (unsigned int i = 0; i < in.size(); ++i)
	{
		character = in[i];
		if (character == '-')
		{
			count++;
		}
	} 
	if (currentIndex == in.size())
	{
		std::set<std::string>::iterator dictFind = dict.find(in);
		if (dictFind != dict.end())
		{
			answers.insert(in);
		}
		return;
	}
	character = in[currentIndex];
	if (character != '-')
	{
			charCombiner(in, currentIndex + 1, floatingCopy, dict, answers);
			return;
	} else
	{
      if (count == floatingCopy.size())
      {
        for (unsigned int j = 0; j < floatingCopy.size(); ++j)
        {
          in[currentIndex] = floatingCopy[j];
          std::string newFloatingCopy = floatingCopy;
          newFloatingCopy.erase(j, 1);
          charCombiner(in, currentIndex + 1, newFloatingCopy, dict, answers); 
        }
		}	else
		{
			for (int i = 0; i < 26; ++i)
			{
				char c = char(i + 97);
				in[currentIndex] = c;
				unsigned int floatingIndex = floatingCopy.find(c);
				if (floatingIndex <= floatingCopy.size())
				{
					std::string newFloatingCopy = floatingCopy;
					newFloatingCopy.erase(floatingIndex, 1);
					charCombiner(in, currentIndex + 1, newFloatingCopy, dict, answers); 
				}
				else
				{
					charCombiner(in, currentIndex + 1, floatingCopy, dict, answers); 
				}
			}
		}
	}
}