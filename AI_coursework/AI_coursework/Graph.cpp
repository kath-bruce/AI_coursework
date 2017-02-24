#include <math.h>
#include "Graph.h"

Graph::Graph(const char * fileName)
{
	parseGraph(fileName);
	goalNode.nodeNum = 60;
}

void Graph::parseGraph(const char * fname)
{
	std::ifstream graphData;
	graphData.open(fname);

	if (!graphData) {
		std::cerr << "error loading " << fname << "\n";
	}

	std::string input;
	std::getline(graphData, input);
	std::stringstream sstream;

	char equals, comma, dash, openSquareBracket, quotation;
	int nodeNum, edgeCost;

	if (input != "graph G {") {
		std::cerr << "problem with file " << fname << "\ngraph G { is not graph G {\n" << input;
	}
	else {
		std::cout << "graph G { is fine\n";
	}

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input);

	if (input != ("graph[splines=\"true\"]")) {
		std::cerr << "problem with file " << fname << "\ngraph[splines = \"true\"] is not graph[splines=\"true\"]\n" << input;
	}
	else {
		std::cout << "graph[splines=\"true\"] is fine\n";
	}

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input);

	if (input != ("node[shape=\"circle\",fixedsize=true,height=0.15]")) {
		std::cerr << "problem with file " << fname << "\nnode[shape=\"circle\",fixedsize=true,height=0.15] is not node[shape=\"circle\",fixedsize=true,height=0.15]\n" << input;
	}
	else {
		std::cout << "node[shape=\"circle\",fixedsize=true,height=0.15] is fine\n";
	}

	while (true) {
		sstream.str("");
		sstream.clear();
		std::getline(graphData, input);
		sstream.str(input);
		sstream >> nodeNum >> openSquareBracket;
		if (openSquareBracket != '[') {
			std::cout << "finished parsing nodes\n";
			break;
		}

		Node newNode;
		newNode.nodeNum = nodeNum;

		sstream >> comma;
		while (comma != ',') {
			sstream >> comma;
			if (comma == ';') {
				std::cerr << "file " << fname << " contains incorrect syntax for node parsing - comma\n";
				break;
			}
		}

		sstream >> equals;
		while (equals != '=') {
			sstream >> equals;
			if (equals == ';') {
				std::cerr << "file " << fname << " contains incorrect syntax for node parsing - equals\n";
				break;
			}
		}

		sstream >> quotation;
		if (quotation != '\"') {
			std::cerr << "file " << fname << " contains incorrect syntax for node parsing - \"\n";
			break;
		}

		Position newPos;
		sstream >> newPos.x >> comma >> newPos.y;

		nodes.insert({ newNode, newPos });
		std::cout << "inserted node " << newNode.nodeNum << " with pos " << newPos.x << "," << newPos.y << std::endl;
		nodeCount++;
	}

	std::cout << "added " << nodeCount << " nodes\n";

	//nodeNum contains first value of first edge and openSquareBracket contains one '-'

	Edge firstEdge;
	firstEdge.from = nodeNum;
	sstream >> dash >> firstEdge.to;

	sstream >> comma;
	while (comma != ',') {
		sstream >> comma;
		if (comma == ';') {
			std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - comma\n";
			break;
		}
	}

	sstream >> equals;
	while (equals != '=') {
		sstream >> equals;
		if (equals == ';') {
			std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - equals\n";
			break;
		}
	}

	sstream >> quotation;
	if (quotation != '\"') {
		std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - \"\n";
	}
	sstream >> edgeCost;

	edges.insert({ firstEdge, edgeCost });

	std::cout << "inserted first edge\n";

	sstream.str("");
	sstream.clear();

	while (std::getline(graphData, input)) {
		sstream.str(input);

		Edge newEdge;
		sstream >> newEdge.from >> dash >> dash >> newEdge.to;

		sstream >> comma;
		while (comma != ',') {
			sstream >> comma;
			if (comma == ';') {
				std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - comma\n";
				break;
			}
		}

		sstream >> equals;
		while (equals != '=') {
			sstream >> equals;
			if (equals == ';') {
				std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - equals\n";
				break;
			}
		}

		sstream >> quotation;
		if (quotation != '\"') {
			std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - \"\n";
		}
		sstream >> edgeCost;

		edges.insert({ newEdge, edgeCost });

		std::cout << "inserted edge " << newEdge.from << " -- " << newEdge.to << " with cost " << edgeCost << "\n";

		sstream.str("");
		sstream.clear();
	}

	std::cout << "inserted edges\n";

	std::cout << "loaded and parsed " << fname << "\n";
	graphData.close();
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

	for (auto edge : edges) {
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
	//loop through edges

	Edge edge;
	edge.from = current.nodeNum;
	edge.to = neighbour.nodeNum;

	if (!edges.count(edge)) {
		edge.from = neighbour.nodeNum;
		edge.to = current.nodeNum;
		if (!edges.count(edge)) {
			return -1;
		}
		else {
			return edges.at(edge);
		}

	}
	else {
		return edges.at(edge);
	}
}

int Graph::heuristic(Node goal, Node next)
{
	//todo: error checking!!!!
	//todo: clean up code
	Position goalPos = nodes.at(goal);
	Position nextPos = nodes.at(next);
	int result = hypot((goalPos.x - nextPos.x), (goalPos.y - nextPos.y));
	//hypotenuse
	return result;
}


