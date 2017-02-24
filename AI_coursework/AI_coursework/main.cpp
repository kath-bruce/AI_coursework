
#include <queue>
#include <vector> 
#include <unordered_map>
#include <chrono>
#include "Graph.h"

//TODO: move a* algorithm to own class
//todo: possibly add user input - just run multiple times - 0-60, 1-61, 0-63
//todo: parse dot graph
//todo: comment code
int main(int argc, char *argv[]) {

	/*

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

	Graph graph("graphData.dot");
	std::priority_queue<Node, std::vector<Node>, std::greater<std::vector<Node>::value_type>> frontier;
	graph.setStartNode(0);
	graph.setGoalNode(60);

	frontier.push(graph.getStartNode());

	std::unordered_map<Node, Node, NodeHasher> came_from;
	std::unordered_map<Node, int, NodeHasher> cost_so_far;

	came_from[graph.getStartNode()] = graph.getStartNode();
	cost_so_far[graph.getStartNode()] = 0;
	int iterations = 0;
	auto t1 = std::chrono::steady_clock::now();

	while (!frontier.empty()) {

		Node current = frontier.top();

		frontier.pop();

		std::cout << "current node: " << current.nodeNum << std::endl;

		if (graph.isGoal(current)) {
			graph.setGoalNode(current);
			std::cout << "reached goal\n";
			break;
		}

		for (Node neighbour : graph.getNeighbours(current)) {
			int heuristic = graph.heuristic(graph.getGoalNode(), neighbour);
			int new_cost = cost_so_far[current] + graph.getCost(current, neighbour);
			if (!cost_so_far.count(neighbour) || new_cost < cost_so_far[neighbour])
			{
				cost_so_far[neighbour] = new_cost;
				neighbour.priority = new_cost + heuristic;
				frontier.push(neighbour);
				came_from[neighbour] = current;
			}

		}
		iterations++;
	}

	auto t2 = std::chrono::steady_clock::now();

	auto totalTime = std::chrono::duration<double>(t2 - t1).count();

	//reconstruct path
	std::vector<Node> path;

	Node current = graph.getGoalNode();

	path.push_back(current);
	int totalCost = 0;
	while (current.nodeNum != graph.getStartNode().nodeNum) {
		totalCost += graph.getCost(current, came_from[current]);
		current = came_from[current];
		path.push_back(current);
	}

	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i].nodeNum << std::endl;
	}

	std::cout << "Total path cost: " << totalCost << std::endl;
	std::cout << "Total time taken: " << totalTime << " seconds\n";
	std::cout << "Iterations: " << iterations << std::endl;

	return 0;
}