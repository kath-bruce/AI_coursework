#include "Graph.h"

#include "Edge.h"

Graph::Graph(const char * fileName)
{
	GraphParser::parseGraph(fileName, nodeCount, edgesNcosts, nodes);
}
