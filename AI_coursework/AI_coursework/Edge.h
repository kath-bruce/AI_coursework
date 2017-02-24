#pragma once
#ifndef EDGE_H
#define EDGE_H

#include <functional>

/*
REFERENCES
http://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key <- hashing for custom struct – using custom struct as key in unordered_map
http://www.learncpp.com/cpp-tutorial/96-overloading-the-comparison-operators/ <- overloading comparison operators
*/

struct Edge {
	int from, to;

	//operator == overloaded as Edge is used as key in unordered maps
	bool operator==(const Edge &other) const {
		return ((from == other.from && to == other.to));
	}
};

//hasher to allow Edge to be used a key in unordered maps
struct EdgeHasher {	
	std::size_t operator()(const Edge &e) const {

		return ((std::hash<int>()(e.from) ^ (std::hash<int>()(e.to)) << 1));
	}
};

#endif

