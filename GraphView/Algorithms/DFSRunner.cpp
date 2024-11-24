#include "DFSRunner.h"
#include "../Entities/Edge.h"
#include "EdgeAnimator.h"
#include <chrono>
#include <thread>

void DFSRunner::run(QtDesignArea* designArea, Handle start, std::optional<Handle>)
{
	if (designArea->isDirected())
	{
		graphlite::algorithm::GraphLiteDFS<decltype(designArea->getDirectedGraph())> dfs{};

		EdgeAnimator edgeAnimator{ designArea };

		auto f = [&](std::optional<Handle> from, Handle to) 
		{
			if (!from.has_value())
				return false;

			Edge* edge = dynamic_cast<Edge*>(designArea->getItem(designArea->getDirectedGraph().edgeData(from.value(), to).value()));
			if (!edge)
				return false;

			edgeAnimator.addEdge(edge);

			return false;
		};

		dfs.DFS(designArea->getDirectedGraph(), start, f);
	}
	else
	{
		graphlite::algorithm::GraphLiteDFS<decltype(designArea->getUndirectedGraph())> dfs{};

		EdgeAnimator edgeAnimator{ designArea };

		auto f = [&](std::optional<Handle> from, Handle to) 
		{
			if (!from.has_value())
				return false;

			Edge* edge = dynamic_cast<Edge*>(designArea->getItem(designArea->getUndirectedGraph().edgeData(from.value(), to).value()));
			if (!edge)
				return false;

			edgeAnimator.addEdge(edge);

			return false;
		};

		dfs.DFS(designArea->getUndirectedGraph(), start, f);
	}
}
