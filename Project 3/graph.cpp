// Do Yun Jason Kim ECE 165
// graph.cpp

#include "graph.h"
using namespace std;

#define INFINITY INT_MAX

//Create Graph
graph::graph(int capacity)
{
    this->vertex_map = new hashTable(capacity);
}

//Create Insert function for vertices
bool graph::insertVertex(std::string id)
{
    if (this->checkVertex(id))
        return false;
    vertex *node = new vertex();
    node->name = id;
    this->vertex_map->insert(id, node);
    this->vertices.push_back(node);
    return true;
}

//Create check function to check for existing nodes
bool graph::checkVertex(std::string id)
{
    return this->vertex_map->contains(id);
}

//Create Insert function for weighted edges
void graph::insertEdge(std::string start, std::string end, int dist)
{
    this->insertVertex(start);
    this->insertVertex(end);
    bool keyExists = false;
    vertex *dest = static_cast<vertex *> (this->vertex_map->getPointer(end, &keyExists));
    edge *ed = new edge();
    ed->cost = dist;
    ed->destination = dest;
    vertex *source = static_cast<vertex *> (this->vertex_map->getPointer(start, &keyExists));
    source->adj.push_back(ed);
    return;
}

//Create function to run dijkstra's algorithm
void graph::dijkstra(std::string sourceVertex)
{
    heap Q(this->vertices.size()+1);
    list<vertex *>::iterator it;
    for (it=this->vertices.begin(); it!=this->vertices.end(); it++)
        {
        if ((*it)->name == sourceVertex)
            (*it)->dist = 0;
        else
            (*it)->dist = INFINITY;
        (*it)->isKnown = false;
        (*it)->prev = NULL;
        Q.insert((*it)->name, (*it)->dist, (*it));
        }
    vertex *node;
    while (Q.deleteMin(NULL,NULL,&node) != 1)
    {
        node->isKnown = true;
        list<edge *>::iterator it2;
        if (node->dist == INFINITY)
            continue;
        for (it2=node->adj.begin(); it2!=node->adj.end(); it2++)
        {
            int newCost = node->dist + (*it2)->cost;
            if (newCost < (*it2)->destination->dist)
            {
                (*it2)->destination->dist = newCost;
                Q.setKey((*it2)->destination->name,newCost);
                (*it2)->destination->prev = node;
            }
        }
    }
    return;
}

//Create a function that would give an output file with the results from dijkstra's
void graph::outputFile(std::string filename)
{
    ofstream out(filename.c_str());
    list<vertex *>::iterator it;
    string path;
    for (it=this->vertices.begin(); it!=this->vertices.end(); it++)
    {
        out << (*it)->name << ": ";
        vertex *node = (*it);
        if (node->dist == INFINITY)
            out << "NO PATH" << endl;
        else if (node->dist == 0)
            out << node->dist << " [" << node->name << "]" << endl;
        else
        {
            out << node->dist << " [";
            path = node->name;
            while (node->prev != NULL) {
                path = node->prev->name + ", " + path;
                node = node->prev;
            }
            out << path << "]" << endl;
        }
    }
    return;
}
