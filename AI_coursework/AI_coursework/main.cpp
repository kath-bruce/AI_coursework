#include <unordered_map>
#include "GraphParser.h"
#include "Edge.h"
#include "Position.h"

int main(int argc, char *argv[]) {
	
	/*
	//nodes will be stored in vector of positions - Position.cpp and header needed
	//came_from = vector/unordered_set/set of nodes(ints)
	//cost_so_far = vector/unordered_set/set of 

	frontier = PriorityQueue() // of nodes
	frontier.put(start, 0)
	came_from = {}
	cost_so_far = {}
	came_from[start] = None
	cost_so_far[start] = 0

	while not frontier.empty():
		current = frontier.get()

		if current == goal:
			break

		for next in graph.neighbors(current):
			new_cost = cost_so_far[current] + graph.cost(current, next)
			if next not in cost_so_far or new_cost < cost_so_far[next]:
				cost_so_far[next] = new_cost
				priority = new_cost + heuristic(goal, next)
				frontier.put(next, priority)
				came_from[next] = current
	*/

	//user input for start and goal node
	//display route - use came_from
	//display total cost

	int nodeCount;
	std::unordered_map<Edge, int, EdgeHasher> edgesNcosts;
	std::unordered_map<int, Position> nodes;


	GraphParser::parseGraph("graphData.txt", nodeCount, edgesNcosts, nodes);

	return 0;
}