//Do Yun Jason Kim ECE 165
//mergeandcheck.cpp
//This program checks if, given three input strings, if the third string is a merge of the first two strings

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

class node
{
public:
	node(int c, char d): count(c), direction(d) {}
	//counter for easy merge check
	//direction to later help with converting letters to uppercase
	unsigned int count;
	char direction;
};

string mergeword(const string &firstword, const string &secondword, string &merge)
{
	string word1, word2, mergedword;
	word1 = " " + firstword;
	word2 = " " + secondword;
	mergedword = " " + merge;
	//n is a placeholder for the other directions
	node item(0, 'n');
	//implement matrix
	int length1 = word1.length();
	int length2 = word2.length();
	vector<node> vec(length2, item);
	vector<vector<node> > matrix(length1, vec);
	for (int i = 0; i < length1; i++)
	{
		for (int j = 0; j < length2; j++)
		{
			if (i > 0 && mergedword[i + j] == word1[i])
			{
				matrix[i][j].count = matrix[i-1][j].count + 1;
				matrix[i][j].direction = 'u';
			}
			if(j > 0 && mergedword[i + j] == word2[j])
			{
				if (matrix[i][j].count <= matrix[i][j-1].count + 1)
				{
					matrix[i][j].count = matrix[i][j-1].count + 1;
					matrix[i][j].direction = 'l';
				}
			}
		}
	}
	int i = length1 - 1, j = length2 - 1;
	if (matrix[i][j].count != merge.length())
		return "*** NOT A MERGE ***";
	else
	{
		while (i != 0 || j != 0)
		{
		    //the direction as seen helps determine which are upper and lower cases
		    //u = upper case
		    //l = lower case
			if (matrix[i][j].direction == 'u')
			{
				merge[i+j-1] = toupper(merge[i+j-1]);
				i--;
			}
			else if (matrix[i][j].direction == 'l')
			{
				j--;
			}
		}
	}
	return merge;
}

//help with possible reading in bugs
void carry_remove(std::string& line)
{
    if (*line.rbegin() == '\r')
    {
        line.erase(line.length() - 1);
    }
}

int main()
{
	string firstword, secondword, merge, filename;
	stringstream buffer;
	cout << "Enter name of input file: ";
	cin >> filename;
	ifstream fin(filename.c_str());
	cout << "Enter name of output file: ";
	cin >> filename;
	ofstream fout(filename.c_str());

	while (!fin.eof())
	{
		getline(fin, firstword);
		getline(fin, secondword);
		getline(fin, merge);
		carry_remove(firstword);
		carry_remove(secondword);
		carry_remove(merge);
		fout << mergeword(firstword, secondword, merge) << endl;
	}

	fin.close();
	fout.close();
	return 0;
}
