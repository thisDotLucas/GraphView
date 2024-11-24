
set(CMAKE_AUTOMOC ON)

add_executable (GraphView "GraphView.cpp" "GraphView.h" "Main.cpp" "UIComponents/Application.h" "UIComponents/Application.cpp" "UIComponents/Window.h" "UIComponents/Window.cpp"
"UIComponents/DesignArea.h" "UIComponents/DesignArea.cpp"  "Entities/Vertex.h" "Entities/Vertex.cpp" "Entities/Edge.h" "Entities/Edge.cpp" "Shapes/Circle.h" "Shapes/Circle.cpp"
"Shapes/Line.h" "Shapes/Line.cpp" "Utils/Point.h" "Entities/Entity.h" "Entities/Entity.cpp" "Utils/Colors.h" "Drawing/DrawingContext.h" "Drawing/VertexDrawingContext.h" "Drawing/EdgeDrawingContext.h"
"Drawing/NoneDrawingContext.h" "Drawing/DrawingContext.cpp" "Drawing/VertexDrawingContext.cpp" "Drawing/EdgeDrawingContext.cpp" "Drawing/NoneDrawingContext.cpp" "Drawing/DrawingFunctions.h"
"Drawing/DrawingFunctions.cpp" "UIComponents/GridScene.h" "UIComponents/SettingsTab.h" "UIComponents/SettingsTab.cpp" "UIComponents/ObjectTab.h" "UIComponents/ObjectTab.cpp" "UIComponents/AlgorithmTab.h"
"UIComponents/AlgorithmTab.cpp" "UIComponents/EdgeObjectTabWidget.h" "UIComponents/EdgeObjectTabWidget.cpp" "UIComponents/VertexObjectTabWidget.h" "UIComponents/VertexObjectTabWidget.cpp"
"Serialization/Serialize.h" "Serialization/Serialize.cpp" "UIComponents/BFSWidget.h" "UIComponents/BFSWidget.cpp" "Algorithms/BFSRunner.h" "Algorithms/BFSRunner.cpp" "Algorithms/Runner.h" "Algorithms/DFSRunner.cpp" "UIComponents/DFSWidget.h" "UIComponents/DFSWidget.cpp" "Algorithms/EdgeAnimator.h" "Algorithms/EdgeAnimator.cpp" "Algorithms/DijkstraRunner.h" "Algorithms/DijkstraRunner.cpp" "UIComponents/DijkstraWidget.h" "UIComponents/DijkstraWidget.cpp" "Algorithms/VertexAnimator.h" "Algorithms/VertexAnimator.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphView PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(CppGraphLite)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets CppGraphLite)
