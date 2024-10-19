
add_executable (GraphView "GraphView.cpp" "GraphView.h" "Main.cpp" "UIComponents/Application.h" "UIComponents/Application.cpp" "UIComponents/Window.h" "UIComponents/Window.cpp"
"UIComponents/DesignArea.h" "UIComponents/DesignArea.cpp"  "Entities/Vertex.h" "Entities/Vertex.cpp" "Entities/Edge.h" "Entities/Edge.cpp" "Shapes/Circle.h" "Shapes/Circle.cpp"
"Shapes/Line.h" "Shapes/Line.cpp" "Utils/Point.h" "Entities/Entity.h" "Entities/Entity.cpp" "Utils/Colors.h" "Drawing/DrawingContext.h" "Drawing/VertexDrawingContext.h" "Drawing/EdgeDrawingContext.h"
"Drawing/NoneDrawingContext.h" "Drawing/DrawingContext.cpp" "Drawing/VertexDrawingContext.cpp" "Drawing/EdgeDrawingContext.cpp" "Drawing/NoneDrawingContext.cpp" "Drawing/DrawingFunctions.h" "Drawing/DrawingFunctions.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphView PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(CppGraphLite)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets CppGraphLite)
