#pragma once
#ifndef NODE_H
#define NODE_H

#include <functional>

/*
REFERENCES
http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key <- hashing for custom struct – using custom struct as key in unordered_map
http://www.learncpp.com/cpp-tutorial/96-overloading-the-comparison-operators/ <- overloading comparison operators
http://www.learncpp.com/cpp-tutorial/96-overloading-the-comparison-operators/ <- friend keyword for operator overloading
http://en.cppreference.com/w/cpp/container/priority_queue <-priority queue
http://www.cplusplus.com/reference/queue/priority_queue/ <-more priority queue
https://support.microsoft.com/en-us/help/837697/how-to-use-the-stl-priority-queue-class-with-a-custom-type <- priority queue with custom class
*/

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
