#pragma once
#include "../UIComponents/DesignArea.h"
#include "../Entities/Edge.h"

class EdgeAnimator
{
public:
	EdgeAnimator(QtDesignArea* designArea);

	~EdgeAnimator();
	
	void addEdge(Edge* edge);
	void setSpeedUp(bool enable) { m_speedUp = enable; }
	
private:
	bool m_speedUp{ false };
	QtDesignArea* m_designArea;
	std::vector<Edge*> m_edges;
};
