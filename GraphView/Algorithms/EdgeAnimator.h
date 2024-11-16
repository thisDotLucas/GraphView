#pragma once
#include "../UIComponents/DesignArea.h"
#include "../Entities/Edge.h"

class EdgeAnimator
{
public:
	EdgeAnimator(QtDesignArea* designArea);

	~EdgeAnimator();
	
	void addEdge(Edge* edge);
	
private:
	QtDesignArea* m_designArea;
	std::vector<Edge*> m_edges;
};
