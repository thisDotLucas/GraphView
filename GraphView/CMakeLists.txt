# CMakeList.txt : CMake project for GraphView, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GraphView "GraphView.cpp" "GraphView.h" "Main.cpp" "UIComponents/Application.h" "UIComponents/Application.cpp" "UIComponents/Window.h" "UIComponents/Window.cpp" "UIComponents/DesignArea.h" "UIComponents/DesignArea.cpp"  "Entities/Vertex.h" "Entities/Vertex.cpp" "Entities/Edge.h" "Entities/Edge.cpp" "Shapes/Circle.h" "Shapes/Circle.cpp" "Shapes/Line.h" "Shapes/Line.cpp" "Utils/Point.h" "Entities/Entity.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphView PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
