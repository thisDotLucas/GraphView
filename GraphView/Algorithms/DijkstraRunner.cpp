#include "DijkstraRunner.h"
#include "VertexAnimator.h"
#include "EdgeAnimator.h"

void DijkstraRunner::run(QtDesignArea* designArea, Handle start, std::optional<Handle> to)
{
	graphlite::algorithm::GraphLiteDijkstra<decltype(designArea->getDirectedGraph())> dijkstra{};

	VertexAnimator animator{ designArea };

	std::vector<Vertex*> m_verticies;
	auto f = [&](Handle vertex) 
	{
		if (auto vertexItem = dynamic_cast<Vertex*>(designArea->getItem(vertex)))
		{
			animator.addVertex(vertexItem);
		}

		return vertex == to.value();
	};
	
	auto getWeight = [&](Handle edge)
	{
		if (auto edgeItem = dynamic_cast<Edge*>(designArea->getItem(edge)))
		{
			return edgeItem->data(1).toInt();
		}

		return std::numeric_limits<int>::max();
	};

	dijkstra.Dijkstra(designArea->getDirectedGraph(), start, f, getWeight);

	if (to.has_value())
	{
		EdgeAnimator pathAnimator{ designArea };
		pathAnimator.setSpeedUp(true);

		std::optional<decltype(designArea->getDirectedGraph())::VertexType> last{ std::nullopt };
		for (auto& vertex : dijkstra.getPath(to.value()))
		{
			if (!last.has_value())
			{
				last = vertex;
				continue;
			}

			pathAnimator.addEdge((Edge*)designArea->getItem(designArea->getDirectedGraph().edgeData(last.value(), vertex).value()));
			last = vertex;
		}
	}
}
