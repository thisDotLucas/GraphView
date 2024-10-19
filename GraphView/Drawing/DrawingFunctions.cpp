#include "DrawingFunctions.h"
#include <QMouseEvent>
#include "../Shapes/Circle.h"
#include "../Entities/Vertex.h"
#include "../Entities/Edge.h"
#include <algorithm>
#include <ranges>

namespace
{
    template<class... Ts>
    struct overloaded : Ts... { using Ts::operator()...; };

    void mousePress(QtDesignArea& designArea, EdgeDrawingContext context, QMouseEvent& e)
    {
		if (e.button() == Qt::MouseButton::LeftButton)
		{
            std::vector<Vertex*> verticies;
            for (auto&& item : designArea.scene()->selectedItems())
            {
                if (auto vertex = dynamic_cast<Vertex*>(item))
                    verticies.push_back(vertex);
            }

            if (verticies.size() == 2)
            {
                for (auto&& item : designArea.scene()->selectedItems())
                    item->setSelected(false);

                auto edge = new Edge{ verticies[0], verticies[1] };
                designArea.scene()->addItem(edge);
                designArea.addEdge(verticies[0], verticies[1], edge);
				designArea.scene()->update();
            }
		}
    }

    void mousePress(QtDesignArea& designArea, VertexDrawingContext context, QMouseEvent& e)
    {	
        if (e.button() == Qt::MouseButton::LeftButton)
		{
            auto vertex = new Vertex{ designArea.mapToScene(e.pos()), Circle{ 15 }, QColor{ 3, 136, 252 } };
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
