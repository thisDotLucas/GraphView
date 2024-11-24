#pragma once
#include "../UIComponents/DesignArea.h"
#include "../Entities/Vertex.h"

class VertexAnimator
{
public:
	VertexAnimator(QtDesignArea* designArea);

	~VertexAnimator();
	
	void addVertex(Vertex* edge);
	
private:
	QtDesignArea* m_designArea;
	std::vector<Vertex*> m_verticies;
};
