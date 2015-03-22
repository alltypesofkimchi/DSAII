// Do Yun Jason Kim ECE 165
// dijkstra.cpp

#include <iostream>
#include <cstdlib>
#include "graph.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
using namespace std;

void loadGraph(graph &myGraph, ifstream &in)
{
    string line, start, end;
    int weight;
    while (getline(in,line))
    {
        istringstream stream(line);
        stream >> start >> end >> weight;
        myGraph.insertEdge(start,end,weight);
    }
    return;
}

int main()
{
    string infile, outfile, vertexStart;
    bool inputGood = false;
    cout << "Enter name of graph file: ";
    cin >> infile;
    ifstream input(infile.c_str());
    if (!input.is_open())
    {
        cout << "Invalid Filename: " << infile << endl;
        exit(1);
    }
    graph myGraph(100);
    loadGraph(myGraph, input);
    while (!inputGood)
    {
        cout << "Enter a valid vertex id for the starting vertex: ";
        cin >> vertexStart;
        if (myGraph.checkVertex(vertexStart))
            inputGood = true;
        else
            cout << "Invalid Vertex: " << vertexStart << endl;
    }
    clock_t t1 = clock();
    myGraph.dijkstra(vertexStart);
    clock_t t2 = clock();
    double algTime = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: ";
    cout << algTime << endl;
    cout << "Enter name of output file: ";
    cin >> outfile;
    myGraph.outputFile(outfile);
    input.close();
    return 0;
}
