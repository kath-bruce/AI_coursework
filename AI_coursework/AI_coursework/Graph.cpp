#include <math.h>
#include "Graph.h"

Graph::Graph(const char * fileName)
{
	parseGraph(fileName);
}

void Graph::parseGraph(const char * fname)
{
	std::ifstream graphData;
	graphData.open(fname);

	if (!graphData) {
		std::cerr << "error loading " << fname << "\n";
	} //end if

	std::string input;
	std::getline(graphData, input);
	std::stringstream sstream;

	char equals, comma, dash, openSquareBracket, quotation;
	int nodeNum, edgeCost;

	//checks first three lines
	if (input != "graph G {") {
		std::cerr << "problem with file " << fname << "\ngraph G { is not graph G {\n" << input;
	} //end if

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input);

	if (input != ("graph[splines=\"true\"]")) {
		std::cerr << "problem with file " << fname << "\ngraph[splines = \"true\"] is not graph[splines=\"true\"]\n" << input;
	} //end if

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input);

	if (input != ("node[shape=\"circle\",fixedsize=true,height=0.15]")) {
		std::cerr << "problem with file " << 
			fname << "\nnode[shape=\"circle\",fixedsize=true,height=0.15] is not node[shape=\"circle\",fixedsize=true,height=0.15]\n" << input;
	} //end if

	//parse nodes and positions
	while (true) {
		sstream.str("");
		sstream.clear();
		std::getline(graphData, input);
		sstream.str(input);
		sstream >> nodeNum >> openSquareBracket;
		if (openSquareBracket != '[') {
			break;
		} //end if

		Node newNode;
		newNode.nodeNum = nodeNum;

		sstream >> comma;
		while (comma != ',') {
			sstream >> comma;
			if (comma == ';') {
				std::cerr << "file " << fname << " contains incorrect syntax for node parsing - comma\n";
				break;
			} //end if
		} //end while loop

		sstream >> equals;
		while (equals != '=') {
			sstream >> equals;
			if (equals == ';') {
				std::cerr << "file " << fname << " contains incorrect syntax for node parsing - equals\n";
				break;
			} //end if
		} //end while loop

		sstream >> quotation;
		if (quotation != '\"') {
			std::cerr << "file " << fname << " contains incorrect syntax for node parsing - \"\n";
			break;
		} //end if

		Position newPos;
		sstream >> newPos.x >> comma >> newPos.y;

		nodes.insert({ newNode, newPos });
		nodeCount++;
	} //end while loop

	//nodeNum contains first value of first edge
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
	} //end while loop

	sstream >> equals;
	while (equals != '=') {
		sstream >> equals;
		if (equals == ';') {
			std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - equals\n";
			break;
		}
	} //end while loop

	sstream >> quotation;
	if (quotation != '\"') {
		std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - \"\n";
	} //end if
	sstream >> edgeCost;

	edges.insert({ firstEdge, edgeCost });

	sstream.str("");
	sstream.clear();

	//parse edges and costs
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
			} //end if
		} //end while loop

		sstream >> equals;
		while (equals != '=') {
			sstream >> equals;
			if (equals == ';') {
				std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - equals\n";
				break;
			} //end if
		} //end while loop

		sstream >> quotation;
		if (quotation != '\"') {
			std::cerr << "file " << fname << " contains incorrect syntax for edge parsing - \"\n";
		} //end if
		sstream >> edgeCost;

		edges.insert({ newEdge, edgeCost });

		sstream.str("");
		sstream.clear();
	} //end while loop
	graphData.close();
}

std::vector<Node> Graph::getNeighbours(Node current)
{
	std::vector<Node> neighbours;

	if (!nodes.count(current)) {	//error checking
		std::cerr << "node not found: " << current.nodeNum << std::endl;
		return neighbours; // neighbours will be null
	} //end if

	//for loop through edges
	//	if edge == current
	//			add to vector
	//end loop

	for (auto edge : edges) {
		if (edge.first.from == current.nodeNum) {
			Node newNode;
			newNode.nodeNum = edge.first.to;
			neighbours.push_back(newNode);
		} //end if
		else if (edge.first.to == current.nodeNum) {	//edge could be from opposite direction
			Node newNode;
			newNode.nodeNum = edge.first.from;
			neighbours.push_back(newNode);
		} //end if
	} //end for loop

	return neighbours;
}

int Graph::getCost(Node current, Node neighbour)
{
	Edge edge;
	edge.from = current.nodeNum;
	edge.to = neighbour.nodeNum;

	if (!edges.count(edge)) {
		edge.from = neighbour.nodeNum;
		edge.to = current.nodeNum;
		if (!edges.count(edge)) {	//edge could be from opposite direction
			return -1;				//error
		}
		else {
			return edges.at(edge);
		} //end if
	}
	else {
		return edges.at(edge);
	} //end if
}

int Graph::heuristic(Node goal, Node next)
{
	if (!nodes.count(goal) || !nodes.count(next)) {	//error checking
		std::cerr << "node not found\n";
		return -1;
	} //end if

	Position goalPos = nodes.at(goal);
	Position nextPos = nodes.at(next);

	int result = hypot((goalPos.x - nextPos.x), (goalPos.y - nextPos.y)); //hypotenuse - distance 'as the crow flies'

	return result;
}


