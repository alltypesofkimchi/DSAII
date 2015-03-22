// Do Yun Jason Kim ECE 165
// graph.h

#ifndef _GRAPH_H
#define _GRAPH_H
#include "hash.h"
#include "heap.h"
#include <iostream>
#include <string>
#include <list>
#include <climits>
#include <fstream>

class graph
{
  public:
    graph(int capacity=100);
    bool insertVertex(std::string id);
    bool checkVertex(std::string id);
    void insertEdge(std::string start, std::string end, int dist);
    void dijkstra(std::string sourceVertex);
    void outputFile(std::string filename);

  private:
    class edge;
    class vertex {
      public:
        std::string name;
        bool isKnown;
        int dist;
        std::list<edge *> adj;
        vertex *prev;
    };

    class edge {
      public:
        int cost;
        vertex *destination;
    };

    std::list<vertex *> vertices;
    hashTable *vertex_map;
};

#endif //_GRAPH_H
