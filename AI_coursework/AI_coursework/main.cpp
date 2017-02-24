
#include <queue>
#include <vector> 
#include <unordered_map>
#include <chrono>
#include "Graph.h"

/*
REFERENCES
http://www.redblobgames.com/pathfinding/a-star/introduction.html <-python a* algorithm
*/

void aStar(Graph graph) {
	std::priority_queue<Node, std::vector<Node>, std::less<std::vector<Node>::value_type>> frontier; //priority queue to hold nodes that can be investigated
	
	frontier.push(graph.getStartNode()); //add the start node

	std::unordered_map<Node, Node, NodeHasher> came_from; //unordered map to store how the algorithm traverses through the graph
	std::unordered_map<Node, int, NodeHasher> cost_so_far; //unordered map to store the cost it took to get to nodes

	//initialise maps
	came_from[graph.getStartNode()] = graph.getStartNode(); //start node came from start node
	cost_so_far[graph.getStartNode()] = 0; //no cost to get to start node

	int iterations = 0;
	auto t1 = std::chrono::steady_clock::now();

	while (!frontier.empty()) { //while there are nodes in the frontier

		Node current = frontier.top();	//current is most promising node - depending on node.priority

		frontier.pop();					//node is being investigated - therefore should not be in frontier

		if (graph.isGoal(current)) { //early exit if goal is found
			break;
		} //end if

		for (Node neighbour : graph.getNeighbours(current)) { //for every node that is connected to current node

			int heuristic = graph.heuristic(graph.getGoalNode(), neighbour);		//calculate distance 'as the crow flies' to goal - underestimates actual cost

			int new_cost = cost_so_far[current] + graph.getCost(current, neighbour); //calculate the cost to get to neighbour ndoe

			//if neighbour has not been visited or new cost to neighbour is smaller that the current cost to neighbour
			if (!cost_so_far.count(neighbour) || new_cost < cost_so_far[neighbour]) { 
				cost_so_far[neighbour] = new_cost;						//assign new cost to neighbour
				neighbour.priority = new_cost + heuristic;				//priority is the cost and estimated distance - allows priority queue to take both into account
				frontier.push(neighbour);								//add neighbour to frontier to be investigated
				came_from[neighbour] = current;							//to get to neighbour, come from current
			} //end if

		} //end for loop

		iterations++;
	} //end while loop

	auto t2 = std::chrono::steady_clock::now();

	auto totalTime = std::chrono::duration<double>(t2 - t1).count();

	//reconstruct path
	std::vector<Node> path;

	Node current = graph.getGoalNode();	//work back from goal
	path.push_back(current);			//add goal to path

	while (current.nodeNum != graph.getStartNode().nodeNum) {
		current = came_from[current];	//node that algorithm visited from current node
		path.push_back(current);		//add node to path
	} //end while loop

	std::cout << "------------------------------------------------\n";

	std::cout << "Path from node " << graph.getStartNode().nodeNum << " to node " << graph.getGoalNode().nodeNum << std::endl;

	std::cout << path[0].nodeNum;
	for (int i = 1; i < path.size(); i++) { //display path
		std::cout<< " >> " << path[i].nodeNum;
	} //end for loop
	
	std::cout << "\nTotal path cost: " << cost_so_far[graph.getGoalNode()] << std::endl;
	std::cout << "Total time taken: " << totalTime << " seconds\n";
	std::cout << "While loop iterations: " << iterations << std::endl;
	std::cout << "Nodes investigated: " << cost_so_far.size() << std::endl;
	std::cout << "------------------------------------------------\n";
}

int main(int argc, char *argv[]) {

	/*
	!!!PYTHON CODE!!!

	frontier = PriorityQueue()
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

	Graph graph("graphdata.dot");

	graph.setStartNode(0);
	graph.setGoalNode(60);

	aStar(graph);

	graph.setStartNode(1);
	graph.setGoalNode(61);

	aStar(graph);

	graph.setStartNode(0);
	graph.setGoalNode(63);

	aStar(graph);

	return 0;
}