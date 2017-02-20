#include <math.h>
#include "Graph.h"

Graph::Graph(const char * fileName)
{
	GraphParser::parseGraph(fileName, nodeCount, edgesNcosts, nodes);
	goalNode.nodeNum = 60;
}

std::vector<Node> Graph::getNeighbours(Node current)
{
	std::vector<Node> neighbours;

	if (current.nodeNum < 0 || current.nodeNum > nodeCount - 1) {
		std::cerr << "value out of bounds: " << current.nodeNum << std::endl;
		return neighbours; // null
	}

	//for loop through edgesNcosts
	//	if current edge.to or edge.from == current
	//		add to vector
	//end loop

	for (auto edge : edgesNcosts) {
		if (edge.first.from == current.nodeNum) {
			Node newNode;
			newNode.nodeNum = edge.first.to;
			neighbours.push_back(newNode);
		}
		else if (edge.first.to == current.nodeNum) {
			Node newNode;
			newNode.nodeNum = edge.first.from;
			neighbours.push_back(newNode);
		}
	}

	return neighbours;
}

int Graph::getCost(Node current, Node neighbour)
{
	//loop through edgesNcosts

	Edge edge;
	edge.from = current.nodeNum;
	edge.to = neighbour.nodeNum;

	if (!edgesNcosts.count(edge)) {
		edge.from = neighbour.nodeNum;
		edge.to = current.nodeNum;
		if (!edgesNcosts.count(edge)) {
			return -1;
		}
		else {
			return edgesNcosts.at(edge);
		}

	}
	else {
		return edgesNcosts.at(edge);
	}

	//return -1;
}

int Graph::heuristic(Node goal, Node next)
{
	//todo: error checking!!!!
	//todo: clean up code
	Position goalPos = nodes.at(goal);
	Position nextPos = nodes.at(next);
	int result = hypot((goalPos.x - nextPos.x), (goalPos.y - nextPos.y))/* * 1.5*/;
	//manhattan distance or hypotenuse
	return result;
	//return abs(goalPos.x - nextPos.x) + abs(goalPos.y - nextPos.y);
}
