#pragma once
#ifndef GRAPH_H
#define GRAPH_H

/*
REFERENCES

http://www.cplusplus.com/forum/general/184889/ <- reading from file
http://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings <- get line delimiter
http://stackoverflow.com/questions/7623650/resetting-a-stringstream <-resetting string stream
http://en.cppreference.com/w/cpp/container/unordered_map/insert <-insertion for unordered_map

*/

#include <unordered_map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Edge.h"
#include "Node.h"
#include "Position.h"

class Graph {
public:
	Graph(const char * fileName);
	void setStartNode(Node startNodeX) { if (startNodeX.nodeNum >= 0 && startNodeX.nodeNum <= nodeCount - 1) startNode = startNodeX; }
	void setStartNode(int nodeNum) { if (nodeNum >= 0 && nodeNum <= nodeCount - 1) startNode.nodeNum = nodeNum; }
	Node getStartNode() { return startNode; }
	void setGoalNode(Node goalNodeX) { if (goalNodeX.nodeNum >= 0 && goalNodeX.nodeNum <= nodeCount - 1) goalNode = goalNodeX;}
	void setGoalNode(int nodeNum) { if (nodeNum >= 0 && nodeNum <= nodeCount - 1) goalNode.nodeNum = nodeNum; }
	Node getGoalNode() { return goalNode; }
	bool isGoal(Node node) { return goalNode.nodeNum == node.nodeNum; }
	std::vector<Node> getNeighbours(Node current);
	int getCost(Node current, Node neighbour);
	int heuristic(Node goal, Node next);
private:
	void parseGraph(const char *fname);
	Node startNode;
	Node goalNode;
	int nodeCount;
	std::unordered_map<Edge, int, EdgeHasher> edges;
	std::unordered_map<Node, Position, NodeHasher> nodes;
};

#endif
