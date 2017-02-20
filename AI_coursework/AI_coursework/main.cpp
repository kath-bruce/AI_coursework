
#include <queue>
#include <vector> 
#include <unordered_map>
#include "Graph.h"

//TODO: move a* algorithm to own class
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

	Graph graph("graphData.txt");
	std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> frontier;

	frontier.push(graph.getStartNode());

	std::unordered_map<Node, Node, NodeHasher> came_from;
	std::unordered_map<Node, int, NodeHasher> cost_so_far;

	came_from[graph.getStartNode()] = graph.getStartNode();
	cost_so_far[graph.getStartNode()] = 0;

	while (!frontier.empty()) {
		Node current = frontier.top();
		//pop from frontier
		frontier.pop();

		if (graph.isGoal(current)) {
			graph.setGoalNode(current);
			std::cout << "reached goal\n";
			break;
		}

		for (auto neighbour : graph.getNeighbours(current)) {
			int new_cost = cost_so_far[current] + graph.getCost(current, neighbour);
			if (!cost_so_far.count(neighbour) || new_cost < cost_so_far[neighbour])
			{
				cost_so_far[neighbour] = new_cost;
				neighbour.priority = new_cost + graph.heuristic(graph.getGoalNode(), neighbour);
				frontier.push(neighbour);
				came_from[neighbour] = current;
			}

		}
		std::cout << "current node: " << current.nodeNum << std::endl;
	}

	//reconstruct path
	std::vector<Node> path;

	Node current = graph.getGoalNode();

	path.push_back(current);
	int totalCost = 0;
	while (current != graph.getStartNode()) {
		totalCost += graph.getCost(current, came_from[current]);
		current = came_from[current];
		path.push_back(current);
	}

	for (int i = 0; i < path.size(); i++) {
		std::cout << path[i].nodeNum << std::endl;
	}

	std::cout << "Total path cost: " << totalCost << std::endl;

	return 0;
}