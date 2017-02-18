#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include "Edge.h"
#include "Position.h"
#include "GraphParser.h"


class Graph {
public:
	Graph(const char * fileName);
	//start node
	//num of nodes
	//unordered map of edges + cost
	//read from file in constructor
	//goal node
	//neighbours - data structure? vector?
	void setStartNode(int startNodeX) { if (startNodeX >= 0 && startNodeX <= nodeCount - 1) startNode = startNodeX; }
	int getStartNode() { return startNode; }
	void setGoalNode(int goalNodeX) { if (goalNodeX >= 0 && goalNodeX <= nodeCount - 1) goalNode = goalNodeX;}
	bool isGoal(int node) { return goalNode == node; }

private:
	int startNode = 0;
	int goalNode = 60;
	int nodeCount;
	std::unordered_map<Edge, int, EdgeHasher> edgesNcosts;
	std::unordered_map<int, Position> nodes;
};

#endif
