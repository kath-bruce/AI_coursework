#pragma once
#ifndef GRAPHPARSER_H
#define GRAPHPARSER_H

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Edge.h"
#include "Position.h"
#include "Graph.h"

class GraphParser {
public:
	static void parseGraph(const char *fname, int &nodeCount, std::unordered_map<Edge, int, EdgeHasher> &edgesNcosts, std::unordered_map<Node, Position, NodeHasher> &nodes);
	// ^^ return graph?
private:
	//parse edgesNcosts
	//parse nodes
};

#endif
