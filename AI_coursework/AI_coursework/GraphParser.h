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

class GraphParser {
public:
	static void parseGraph(const char *fname, int &nodeCount, std::unordered_map<Edge, int, EdgeHasher> &edgesNcosts, std::unordered_map<int, Position> &nodes);
	
private:
	//parse edgesNcosts
	//parse nodes
};

#endif
