//Do Yun Jason Kim
//DSA II
// Assignment 1: spell check

#include <iostream>
#include "hash.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <algorithm>
using namespace std;

//Provided a dictionary with 250000 words
hashTable dict(2000000);

void loadDictionary(ifstream &dict_file);
int spellCheck(ifstream &input, ofstream &output);

int main()
{
	string inputName;
	string outputName;
	cout << "Enter name of dictionary: ";
	cin >> inputName;
	ifstream input(inputName.c_str());
	if (input == NULL)
    {
		cerr << "Error: could not open " << inputName << endl;
		exit(1);
	}
	//dictionary load time
	clock_t t1 = clock();
	loadDictionary(input);
	clock_t t2 = clock();
	cout << "Total time (in seconds) to load dictionary: " << (double(t2-t1))/CLOCKS_PER_SEC << endl;
	input.close();
	//Input document to be spell-checked
	cout << "Enter name of input file: ";
	cin >> inputName;
	cout << "Enter name of output file: ";
	cin >> outputName;
	ifstream fileToSpellCheck(inputName.c_str());
	ofstream fileToOutput(outputName.c_str());
	//Spell-check time
	t1 = clock();
	int checkSuccess = spellCheck(fileToSpellCheck, fileToOutput);
	t2 = clock();
	cout <<  "Total time (in seconds) to check document: " << double((t2-t1))/CLOCKS_PER_SEC << endl;
	return 0;
}

// Loads the Dictionary
void loadDictionary(ifstream &dict_file)
{
	string word;
	int x;
	while (getline(dict_file, word))
    {
		transform(word.begin(), word.end(), word.begin(), ::tolower);
		dict.insert(word);
		x=dict.fp(word); //cout<<x<<endl;
	}
	return;
}


//SpellCheck
int spellCheck(ifstream &input, ofstream &output)
{
	string validcharacters = "abcdefghijklmnopqrstuvwxyz0123456789\'-";
	string numbers = "0123456789";
	string line;
	string word;
	int x;
	int lineNumber = 1, start = 0, end = 0;

	while(getline(input, line))
    {
		// Make Lowercase and Skip Blank Lines
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		if(line.length() == 0)
		{
			lineNumber++;
			continue;
		}
        // Words must satisfy these conditions:
		// Cannot contain numbers
		// Cannot be longer than 20 characters
		// Must be contained in dictionary
		start = line.find_first_of(validcharacters);
		while (start != string::npos)
        {
            end = line.find_first_not_of(validcharacters, start);
            word = line.substr(start,end-start);
            //cout << word << endl;
            //x=dict.fp(word);
            //cout <<"fp" <<x << endl;
            start = line.find_first_of(validcharacters, end);

            if (word.find_first_of(numbers) != string::npos)
                continue;
            else if (word.length() > 20)
            {
                output << "Long word at line " << lineNumber << ", starts: " << word.substr(0,20) << endl;
            }
            else if (!dict.contains(word))
            {
                //cout << "Unknown word at line " << lineNumber << ": " << word << endl;
                //cout << word << endl;
                //cout << dict << endl;
                output << "Unknown word at line " << lineNumber << ": " << word << endl;
            }
            else if (end == string::npos)
            {
                break;
			}

        }
        lineNumber++;
    }
    return 0;
}
