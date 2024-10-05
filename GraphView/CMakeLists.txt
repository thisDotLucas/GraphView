# CMakeList.txt : CMake project for GraphView, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (GraphView "GraphView.cpp" "GraphView.h" "Main.cpp" "Adapters/Application.h" "Adapters/Application.cpp" "Adapters/Window.h" "Adapters/Window.cpp" "Adapters/DesignArea.h" "Adapters/DesignArea.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GraphView PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Widgets)
