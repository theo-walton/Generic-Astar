
#include "AStar.class.hpp"

template<class T, class W>
bool	AStar<T, W>::Node::operator > (const AStar::Node &obj) const
{
	return (weight > obj.weight) ? true : false;
}

template<class T, class W>
std::vector<typename AStar<T, W>::Node>	AStar<T, W>::GenerateNodesFromIndex(int index)
{
	std::vector<typename Graph<T, W>::Edge> edges = _graph->GetLinks(index);
	std::vector<Node> nodes;

	for (int i = 0; i < edges.size(); i++)
	{
		Node n = {edges[i].destination,
			  edges[i].weight + _distancesFromStart[index],
			  edges[i].weight + _distancesFromStart[index],
			  index};

		n.weight += _heuristic(_graph, edges[i].destination);
		nodes.push_back(n);
	}
	return nodes;
}

template<class T, class W>
void	AStar<T, W>::AddNodesToContainer(std::vector<typename AStar<T, W>::Node> &nodes)
{
	for (Node &node : nodes)
		_availableNodes.push(node);
}

template<class T, class W>
AStar<T, W>::AStar(Graph<T, W> *g, int startIndex, int endIndex) : _graph(g),
								 _start(startIndex),
								 _end(endIndex)
{
	for (int i = 0; i < _graph->Size(); i++)
	{
		_nodeLinks.push_back(0);
		_distancesFromStart.push_back(0);
		_nodesTraversed.push_back(false);
	}
}

template<class T, class W>
void	AStar<T, W>::UseHeuristic(std::function<W(Graph<T, W>*, int)> h)
{
	_heuristic = h;
}

template<class T, class W>
bool	AStar<T, W>::Solve(void)
{
	std::vector<Node> nodes;
	Node temp;

	temp.index = _start;
	_nodesTraversed[_start] = true;	
	while (1)
	{
		nodes = GenerateNodesFromIndex(temp.index);
		AddNodesToContainer(nodes);

		if (!_availableNodes.size())
			return false;
		temp = _availableNodes.top();
		_availableNodes.pop();
		while (_nodesTraversed[temp.index])
		{
			if (!_availableNodes.size())
				return false;
			temp = _availableNodes.top();
			_availableNodes.pop();
		}
		
		_nodeLinks[temp.index] = temp.from;
		_distancesFromStart[temp.index] = temp.trueWeight;
		_nodesTraversed[temp.index] = true;
		if (temp.index == _end)
			break;
	}
	return true;
}

template<class T, class W>
std::vector<T>	AStar<T, W>::GetPath(void)
{
	std::vector<T> path;
	int index = _end;
	
	while (1)
	{
		path.push_back(_graph->NodeFromIndex(index));
		if (index == _start)
			break;
		index = _nodeLinks[index];
	}
	std::reverse(path.begin(), path.end());
	return path;
}

template<class T, class W>
W	AStar<T, W>::GetWeight(void)
{
	return _distancesFromStart[_end];	
}
