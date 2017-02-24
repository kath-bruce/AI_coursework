#pragma once
#ifndef NODE_H
#define NODE_H

#include <functional>

struct Node {
	int nodeNum = 0;
	int priority = 0;

	//operator < overloaded as Node is used in priority queue
	friend bool operator< (const Node& n1, const Node& n2) {
		return (n1.priority < n2.priority);
	}

	//operator > overloaded as Node is used in priority queue
	friend bool operator> (const Node& n1, const Node& n2) {
		return (n1.priority > n2.priority);
	}

	//operator == overloaded as Node is used as key in unordered maps
	bool operator==(const Node &other) const {
		return (nodeNum == other.nodeNum);
	}
};

//hasher to allow Node to be used a key in unordered maps
struct NodeHasher {
	std::size_t operator()(const Node &n) const {
		return ((std::hash<int>()(n.nodeNum)));
	}
};

#endif
