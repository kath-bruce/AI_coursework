#pragma once
#ifndef EDGE_H
#define EDGE_H

#include <functional>

struct Edge {
	int from, to;

	bool operator==(const Edge &other) const {
		return ((from == other.from && to == other.to) ^ (from == other.to && to == other.from));
	}
};

struct EdgeHasher {
	std::size_t operator()(const Edge &e) const {

		return ((std::hash<int>()(e.from) ^ (std::hash<int>()(e.to)) << 1));
	}
};

#endif

