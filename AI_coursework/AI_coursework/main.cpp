
#include <queue>
#include <vector> 
#include <unordered_map>
#include <chrono>
#include "Graph.h"

//Node getTop(std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> frontier) { // problem here
//	std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> frontierCopy = frontier;
//	std::vector<Node> frontierVec;
//	while (!frontierCopy.empty()) {
//		frontierVec.push_back(frontierCopy.top());
//		frontierCopy.pop();
//	}
//	Node top = frontierVec[0];
//
//	for (Node node : frontierVec) {
//		if (node.priority <= top.priority) {
//			if (node.heuristicCost < top.heuristicCost) {
//				top = node;
//			}
//		}
//	}
//
//	//ugh
//	//shove frontier into vec
//	//find node that way
//
//	return top;
//}
//
//void removeTop(std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> &frontier, Node top) {
//	std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> frontierCopy = frontier;
//	std::vector<Node> frontierVec;
//	while (!frontierCopy.empty()) {
//		frontierVec.push_back(frontierCopy.top());
//		frontierCopy.pop();
//	}
//	//frontierCopy = frontier;
//	//Node node;
//	for (int i = 0; i < frontierVec.size(); i++) {
//		if (frontierVec[i] == top) {
//			frontierVec.erase(frontierVec.begin() + i);
//		}
//	}
//
//	for (Node node : frontierVec) {
//		frontierCopy.push(node);
//	}
//
//	frontier = frontierCopy;
//	//return frontier instead of all this assignment and reassignment - nah
//}
//
//bool containsNode(std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> frontier , Node node) {
//	while (!frontier.empty()) {
//		if (node == frontier.top())
//			return true;
//
//		frontier.pop();
//	}
//	return false;
//}

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
	std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> frontier; // maybe doesn't need to be priority queue
	//std::vector<Node> frontierVec;
	graph.setStartNode(1);
	graph.setGoalNode(61);

	frontier.push(graph.getStartNode());
	//frontierVec.push_back(graph.getStartNode());

	std::unordered_map<Node, Node, NodeHasher> came_from;
	std::unordered_map<Node, int, NodeHasher> cost_so_far;

	came_from[graph.getStartNode()] = graph.getStartNode();
	cost_so_far[graph.getStartNode()] = 0;
	int iterations = 0;
	auto t1 = std::chrono::steady_clock::now();

	while (!frontier.empty()) {

		//CURRENT SHOULD BE SOMETHING DIFFERENT??!¬?!?!?!??!?
		//current should be the one with the better heuristic?? (less or greater than)

		Node current = frontier.top();
		//Node current = getTop(frontier);
		//pop from frontier
		frontier.pop();
		//removeTop(frontier, current);

		std::cout << "current node: " << current.nodeNum << std::endl;

		if (graph.isGoal(current)) {
			graph.setGoalNode(current);
			std::cout << "reached goal\n";
			break;
		}

		for (Node neighbour : graph.getNeighbours(current)) {
			int heuristic = graph.heuristic(graph.getGoalNode(), neighbour);
			int new_cost = cost_so_far[current] + graph.getCost(current, neighbour);//heuristic;
			//int new_cost = current.cost_so_far + heuristic;
			if (!cost_so_far.count(neighbour)/*!containsNode(frontier, neighbour)*/ || new_cost < cost_so_far[neighbour])
			{
				cost_so_far[neighbour] = new_cost;
				//neighbour.cost_so_far = new_cost;
				neighbour.heuristicCost = heuristic;
				neighbour.priority = new_cost + heuristic;
				frontier.push(neighbour);
				came_from[neighbour] = current; // change this??
			} //^^^ conflict between priority (gcost in c# example) and cost_so_far????

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