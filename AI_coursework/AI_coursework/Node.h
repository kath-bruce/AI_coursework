#pragma once
#ifndef NODE_H
#define NODE_H

#include <functional>

struct Node {
	int nodeNum = 0;
	int priority = 0;
	int heuristicCost = 0;

	friend bool operator< (const Node& n1, const Node& n2) {
		/*if (n1.priority > n2.priority) {
			if (n1.heuristicCost > n2.heuristicCost) {
				return true;
			}
		}*/
		return (n1.priority > n2.priority/* && n1.heuristicCost > n2.heuristicCost*/);
		//return false;
	}

	friend bool operator> (const Node& n1, const Node& n2) {
		/*if (n1.priority <= n2.priority) {
			if (n1.heuristicCost > n2.heuristicCost) {
				return true;
			}
		}*/

		return (n1.priority < n2.priority/* ^ n1.heuristicCost < n2.heuristicCost*/);
		//return false;
	}

	bool operator==(const Node &other) const {
		return (nodeNum == other.nodeNum && priority == other.priority && heuristicCost == other.heuristicCost); // if i include comparing the priorities
																													 // effects path result??? - doesn't actually
																													 // - came_from[] bug
	}

	//bool operator!=(const Node &other) const {
	//	return (nodeNum != other.nodeNum/* || priority != other.priority || heuristicCost != other.heuristicCost*/);
	//}
};

struct NodeComparator {
	bool operator() (Node n1, Node n2) const {
		if (n1.priority > n2.priority) {
			if (n1.heuristicCost > n2.heuristicCost) {
				return true;
			}
		}
		return false;
	}
};

struct NodeHasher {
	std::size_t operator()(const Node &n) const {
		return ((std::hash<int>()(n.nodeNum) ^ (std::hash<int>()(n.priority)/*) ^ (std::hash<int>()(n.heuristicCost)*//* << 1*/)));
	}
};

#endif
