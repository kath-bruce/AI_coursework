#pragma once
#ifndef NODE_H
#define NODE_H

#include <functional>

struct Node {
	int nodeNum = 0;
	int priority = 0;

	friend bool operator< (const Node& n1, const Node& n2) {
		return (n1.priority < n2.priority);
	}

	friend bool operator> (const Node& n1, const Node& n2) {
		return (n1.priority > n2.priority);
	}

	bool operator==(const Node &other) const {
		return (nodeNum == other.nodeNum);
	}
};

struct NodeHasher {
	std::size_t operator()(const Node &n) const {
		return ((std::hash<int>()(n.nodeNum)));
	}
};

#endif
