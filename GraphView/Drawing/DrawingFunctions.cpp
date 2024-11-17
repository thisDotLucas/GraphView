#include "DrawingFunctions.h"
#include <QMouseEvent>
#include "../Shapes/Circle.h"
#include "../Entities/Vertex.h"
#include "../Entities/Edge.h"
#include <algorithm>
#include <ranges>
#include "../UIComponents/GridScene.h"

namespace
{
    template<class... Ts>
    struct overloaded : Ts... { using Ts::operator()...; };

    void mousePress(QtDesignArea& designArea, EdgeDrawingContext context, QMouseEvent& e)
    {
		if (e.button() == Qt::MouseButton::LeftButton)
		{
            std::vector<Vertex*> verticies;
            for (auto&& item : ((Grid*)designArea.scene())->getSelectionOrder())
            {
                if (auto vertex = dynamic_cast<Vertex*>(item))
                    verticies.push_back(vertex);
            }

            if (verticies.size() == 2)
            {
                designArea.scene()->clearSelection();

                auto edge = new Edge{ verticies[0], verticies[1] };
                designArea.scene()->addItem(edge);
                designArea.addEdge(verticies[0], verticies[1], edge);
                designArea.scene()->update();
                ((Grid*)designArea.scene())->removeFirstFromSelectionOrder();
            }
		}
    }

    void mousePress(QtDesignArea& designArea, VertexDrawingContext context, QMouseEvent& e)
    {	
        if (e.button() == Qt::MouseButton::LeftButton)
		{
            auto vertex = new Vertex{ designArea.mapToScene(e.pos()), Circle{ 15 } };
			designArea.scene()->addItem(vertex);
            designArea.addVertex(vertex);
			designArea.scene()->update();
		}
    }

    void mousePress(QtDesignArea& designArea, NoneDrawingContext context, QMouseEvent& e)
    {
    }
}

Qt::CursorShape getCursorShape(DrawingContext context)
{
    return std::visit(overloaded{
        [](EdgeDrawingContext context) { return Qt::CursorShape::CrossCursor; },
		[](VertexDrawingContext context) { return Qt::CursorShape::CrossCursor; },
		[](NoneDrawingContext context) { return Qt::CursorShape::ArrowCursor; }
    }, context);
}

void mousePress(QtDesignArea& designArea, DrawingContext context, QMouseEvent& e)
{
    std::visit(overloaded{
        [&](EdgeDrawingContext context) { mousePress(designArea, context, e); },
		[&](VertexDrawingContext context) { mousePress(designArea, context, e); },
		[&](NoneDrawingContext context) { mousePress(designArea, context, e); }
    }, context);
}
