#ifndef GRAPH_CLASS_HPP
#define GRAPH_CLASS_HPP

#include <vector>
#include <map>

template <class T, class W = float>
class	Graph
{
public: struct Edge
{
	int destination;
	W weight;
};
	
private:

	std::vector<std::vector<Edge> > _graph;
	std::map<T, int> _idAssociation;
	std::vector<T> _nodes;

public:

	void	AddNode(T id);
	void	AddLink(T id1, T id2, W weight);
	void	AddLinkByIndex(int index1, int index2, W weight);

	int	Size(void);
	bool	IsNode(T id);
	int	IndexOf(T id);
	int	TotalLinks(int index);
	std::vector<Edge>	&GetLinks(int index);
	T	NodeFromIndex(int index);
};

#include "Graph.template.hpp"

#endif
