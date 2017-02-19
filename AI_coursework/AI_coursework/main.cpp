
#include <queue>
#include <vector> // needed?
#include <unordered_map>
#include "Graph.h"

//TODO: move a* algorithm to own class
int main(int argc, char *argv[]) {

	/*
	//nodes are ints with positions
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
	//display time taken

	Graph graph("graphData.txt");

	std::priority_queue<Node, std::vector<Node>, std::greater<std::vector<Node>::value_type>> frontier; // priority queue may need to be less than ordered

	frontier.push(graph.getStartNode());
	//frontier.push(100);
	//frontier.push(50);

	//std::cout << frontier.top() << std::endl;

	std::unordered_map<Node, Node, NodeHasher> came_from;
	std::unordered_map<Node, int, NodeHasher> cost_so_far;

	came_from.insert({ graph.getStartNode(), Node() }); // startnode had no prior node (-1)
	cost_so_far.insert({ graph.getStartNode(), 0 }); //just started so no travel cost

	while (!frontier.empty()) {
		Node current = frontier.top();

		if (graph.isGoal(current)) {
			std::cout << "reached goal\n";
			break;
		}

		for (auto neighbour : graph.getNeighbours(current)) {
			int new_cost = cost_so_far.at(current) + graph.getCost(current, neighbour);
			if (!cost_so_far.count(neighbour) || new_cost < cost_so_far.at(neighbour))
			{
				//cost_so_far.at(neighbour) = new_cost;
				neighbour.priority = new_cost + graph.heuristic(graph.getGoalNode(), neighbour);
				frontier.push(neighbour);
				came_from.insert({ neighbour,current });
				cost_so_far.insert({ neighbour, new_cost });
			}

		}
		//pop from frontier
		frontier.pop();
		std::cout << "current node: " << current.nodeNum << std::endl;
	}

	return 0;
}