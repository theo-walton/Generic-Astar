
#include "Graph.class.hpp"

template <class T, class W>
void	Graph<T, W>::AddNode(T id)
{
	std::vector<Edge> node;
	
	_idAssociation[id] = _nodes.size();
	_nodes.push_back(id);
	_graph.push_back(node);
}

template <class T, class W>
void	Graph<T, W>::AddLink(T id1, T id2, W weight)
{
	int index1 = _idAssociation.find(id1)->second;
	int index2 = _idAssociation.find(id2)->second;

	Edge edge = {index2, weight};
	
	_graph[index1].push_back(edge);
}

template <class T, class W>
void	Graph<T, W>::AddLinkByIndex(int index1, int index2, W weight)
{
	Edge edge = {index2, weight};

	_graph[index1].push_back(edge);
}

template <class T, class W>
int	Graph<T, W>::Size(void)
{
	return _nodes.size();
}

template <class T, class W>
bool	Graph<T, W>::IsNode(T id)
{
	return ( _idAssociation.find(id) == _idAssociation.end() ) ? false : true;
}

template <class T, class W>
int	Graph<T, W>::IndexOf(T id)
{
	return _idAssociation.find(id)->second;
}

template <class T, class W>
int	Graph<T, W>::TotalLinks(int index)
{
	return _graph[index].size();
}

template <class T, class W>
std::vector<typename Graph<T, W>::Edge>	&Graph<T, W>::GetLinks(int index)
{
	return _graph[index];
}

template <class T, class W>
T	Graph<T, W>::NodeFromIndex(int index)
{
	return _nodes[index];
}

