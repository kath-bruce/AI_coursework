#include "GraphParser.h"

void GraphParser::parseGraph(const char * fname, int & nodeCount, std::unordered_map<Edge, int, EdgeHasher>& edgesNcosts, std::unordered_map<int, Position>& nodes)
{
	std::ifstream graphData;
	graphData.open(fname);

	if (!graphData)
		std::cout << "error loading " << fname << "\n";


	std::string input;

	while (std::getline(graphData, input)) {
		std::cout << input << std::endl;
	}

	std::cout << "loaded " << fname << "\n";
	graphData.close();
}
