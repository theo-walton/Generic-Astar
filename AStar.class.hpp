#ifndef ASTAR_CLASS_HPP
#define ASTAR_CLASS_HPP

#include "Graph.class.hpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

template <class T, class W = float>
class	AStar
{

public: struct Node
{
	int index;
	W trueWeight;
	W weight;
	int from;

	bool	operator > (const Node &obj) const;
};
	
private:

	Graph<T, W> *_graph;
	int _start;
	int _end;	
	std::function<W(Graph<T, W>*, int)> _heuristic;
	std::priority_queue<Node, std::vector<Node>, std::greater<Node> > _availableNodes;
	std::vector<int> _nodeLinks;
	std::vector<W> _distancesFromStart;
	std::vector<bool> _nodesTraversed;

	std::vector<Node>	GenerateNodesFromIndex(int index);
	void	AddNodesToContainer(std::vector<Node> &nodes);
	
public:
	
	AStar(Graph<T, W> *g, int startIndex, int endIndex);
	
	void	UseHeuristic(std::function<W(Graph<T, W>*, int)> h);
	bool	Solve(void);
	std::vector<T>	GetPath(void);
	W	GetWeight(void);
};

#include "AStar.template.hpp"

#endif
