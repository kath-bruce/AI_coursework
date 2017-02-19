#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include "Edge.h"
#include "Node.h"
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
	void setStartNode(Node startNodeX) { if (startNodeX.nodeNum >= 0 && startNodeX.nodeNum <= nodeCount - 1) startNode = startNodeX; }
	Node getStartNode() { return startNode; }
	void setGoalNode(Node goalNodeX) { if (goalNodeX.nodeNum >= 0 && goalNodeX.nodeNum <= nodeCount - 1) goalNode = goalNodeX;}
	Node getGoalNode() { return goalNode; }
	bool isGoal(Node node) { return goalNode.nodeNum == node.nodeNum; }
	std::vector<Node> getNeighbours(Node current);
	int getCost(Node current, Node neighbour);
	int heuristic(Node goal, Node next);
private:
	Node startNode;
	Node goalNode;
	int nodeCount;
	std::unordered_map<Edge, int, EdgeHasher> edgesNcosts;
	std::unordered_map<Node, Position, NodeHasher> nodes;
};

#endif
