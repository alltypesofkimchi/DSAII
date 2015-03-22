//Do Yun Jason Kim ECE 165
//mergeandcheck.cpp
//This program checks if, given three input strings, if the third string is a merge of the first two strings

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

#define length 1001

itn matrix[length][length] = {0};

int main()
{
    string input, output;
    cout << "Enter name of input file: ";
    cin >> input;
    cout << "Enter name of output file: ";
    cin >> output;
    ifstream in(input.c_str());
    ofstream out(output.c_str());

    string a,b,c;
    while (getline(input,a) && getline(input,b) && getline(input.c))
    {
        //create a matrix
        for (int i=0; i< length; i++)
        {
            for (int j=0; j<length; j++)
            {
                matrix[i][j] = 0;
            }
        }
        int a_length = a.length(), b_length = b.length(), c_length = c.length();
        //check to see if the lengths match
        //if they do not, then we know it's not a merge so we continue to next set of strings
        if (c_length != a_length + b_length)
        {
            out << "*** NOT A MERGE ***" << endl;
            continue;
        }
        //fill in the matrix
        for (int x=0; x<a_length; x++)
        {
            for (int y=0; y<b_length; y++)
            {
                if (matrix[x][y])
                {
                    if (c[x+y] == a[x])
                        matrix[x+1][y] = 1;
                    if (c[x+y] == b[x])
                        matrix[x][y+1] = 1;
                }
            }
        }
        //check to see if input satisfy merge conditions
        //if so display one string as capital letters and the other as lower
        //if not display not a merge sign
        if (matrix[a_length][b_length] == 1)
        {
            int i = a_length, j = b_length;
            while (i>0 && j>=0)
            {
                if (matrix[i][j] == 1 && (j == 0 || matrix [i][j-1] == 0))
                {
                    c[i+j-1] = toupper(c[i+j-1]);
                    i--;
                }
                else
                {
                    j--;
                }
            }
            out << c << endl;
        }
        else
        {
            out << "*** NOT A MERGE ***" << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}



































