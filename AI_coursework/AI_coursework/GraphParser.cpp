#include "GraphParser.h"

void GraphParser::parseGraph(const char * fname, int & nodeCount, std::unordered_map<Edge, int, EdgeHasher>& edgesNcosts, std::unordered_map<int, Position>& nodes)
{
	// TODO move var declarations

	std::ifstream graphData;
	graphData.open(fname);

	if (!graphData) {
		std::cerr << "error loading " << fname << "\n";
	}

	std::string input;
	std::getline(graphData, input);
	std::stringstream sstream(input);

	char g, equals, comma, dash;
	std::string nodeStr, nodeposStr, edgesAndCostsStr, posStr;
	int nodeNum, edgeCost;

	sstream >> g;

	if (!g == 'g') {
		std::cerr << "problem with file " << fname << "\ng is not g\n" << g;
	}
	else {
		std::cout << "g is fine\n";
	}

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input, '=');
	
	sstream.str(input);

	sstream >> nodeStr;

	if (nodeStr != "nodes") {
		std::cerr << "problem with file " << fname << "\nnodes is not nodes\n" << nodeStr << "\n";
	}
	else {
		std::cout << "nodes is fine\n";
	}

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input);

	sstream.str(input);

	sstream >> nodeCount;
	std::cout << "nodeCount: " << nodeCount << "\n";

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input);

	sstream.str(input);

	sstream >> nodeposStr;

	if (nodeposStr != "nodepos") {
		std::cerr << "problem with file " << fname << "\nnodepos is not nodepos\n" << nodeposStr << "\n";
	}
	else {
		std::cout << "nodepos is fine\n";
	}

	for (int i = 0; i < nodeCount; i++) {
		sstream.str("");
		sstream.clear();
		std::getline(graphData, input, '=');

		sstream.str(input);
		sstream >> nodeNum;
		if (nodeNum != i) {
			std::cerr << "problem with file " << fname << "\nnodenum does not match up with i\ni: " << i << "\n";
		}

		sstream.str("");
		sstream.clear();
		std::getline(graphData, input, '=');

		sstream.str(input);

		sstream >> posStr;
		if (posStr != "pos") {
			std::cerr << "problem with file " << fname << "\n=pos= is not =pos=\ni: " << i << "\n" << posStr << "\n";
		}

		sstream.str("");
		sstream.clear();
		std::getline(graphData, input);

		sstream.str(input);
		Position position;
		sstream >> position.x >> comma >> position.y;

		if (comma != ',') {
			std::cout << "comma is not comma\n" << comma << " i: " << i << "\n";
		}

		nodes.insert({i, position});
	}
	std::cout << "nodes inserted\n";

	sstream.str("");
	sstream.clear();
	std::getline(graphData, input);
	sstream.str(input);

	sstream >> edgesAndCostsStr;

	if (edgesAndCostsStr != "edges+cost") {
		std::cerr << "problem with file " << fname << "\nedges+cost is not edges+cost\n" << edgesAndCostsStr << "\n";
	}
	else {
		std::cout << "edges+cost is fine\n";
	}

	sstream.str("");
	sstream.clear();

	while (std::getline(graphData, input)) {
		sstream.str(input);
		Edge edge;
		sstream >> edge.from >> dash >> edge.to;
		if (edge.from < 0 || edge.from > nodeCount - 1 || edge.to < 0 || edge.to > nodeCount - 1) {
			std::cerr << "problem with file " << fname << "\nedges outside of bounds\n" << edge.from << " " << edge.to << "\n";
 		}
		else if (dash != '-') {
			std::cout << "dash is not dash\n" << dash << " " << edge.from << " " << edge.to << "\n";
		}
		sstream >> equals;
		if (equals != '=') {
			std::cout << "equals is not equals\n" << equals << " " << edge.from << " " << edge.to << "\n";
		}
		sstream >> edgeCost;
		edgesNcosts.insert({ edge, edgeCost });
		sstream.str("");
		sstream.clear();
	}
	std::cout << "edges and costs inserted\n";

	std::cout << "loaded and parsed " << fname << "\n";
	graphData.close();
}
